#include "vod/transcode/job_store.h"

#include <mysql/mysql.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using Connection = std::unique_ptr<MYSQL, decltype(&mysql_close)>;
using Result = std::unique_ptr<MYSQL_RES, decltype(&mysql_free_result)>;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

std::string environment(const char* name) {
    const char* value = std::getenv(name);
    require(value != nullptr, name);
    return value;
}

void query(MYSQL* db, const char* sql) {
    if (mysql_query(db, sql)) throw std::runtime_error(mysql_error(db));
}

std::vector<std::string> readRow(MYSQL* db, const char* sql) {
    query(db, sql);
    Result result(mysql_store_result(db), mysql_free_result);
    require(result && mysql_num_rows(result.get()) == 1, "expected exactly one row");
    MYSQL_ROW row = mysql_fetch_row(result.get());
    std::vector<std::string> values;
    for (unsigned col = 0; col < mysql_num_fields(result.get()); ++col) {
        values.emplace_back(row[col] ? row[col] : "<NULL>");
    }
    return values;
}
}

int main() {
    try {
        vod::user::DatabaseConfig config;
        config.host = environment("VOD_TEST_DB_HOST");
        config.database = environment("VOD_TEST_DB_NAME");
        require(config.host == "127.0.0.1" && config.database == "vod_test",
                "run through the isolated CTest fixture");
        config.user = environment("VOD_TEST_DB_USER");
        config.password = environment("VOD_TEST_DB_PASSWORD");
        const auto port = std::stoul(environment("VOD_TEST_DB_PORT"));
        require(port > 0 && port <= 65535, "invalid test database port");
        config.port = static_cast<std::uint16_t>(port);
        Connection db(mysql_init(nullptr), mysql_close);
        require(db && mysql_real_connect(db.get(), config.host.c_str(), config.user.c_str(),
                                         config.password.c_str(), config.database.c_str(),
                                         config.port, nullptr, 0), "test database connection failed");
        query(db.get(), "INSERT INTO vod_videos (video_id,owner_id,title,description,status,created_at) "
                        "VALUES ('lease-case','lease-owner','lease test','',5,UTC_TIMESTAMP())");
        query(db.get(), "INSERT INTO vod_transcode_jobs (video_id,source_file_id,created_at) "
                        "VALUES ('lease-case','lease/source',UTC_TIMESTAMP())");
        query(db.get(), "INSERT INTO vod_files (file_id,owner_id,size_bytes,created_at) "
                        "VALUES ('lease/b-playlist','lease-owner',1,UTC_TIMESTAMP())");

        vod::transcode::JobStore workerA(config);
        vod::transcode::JobStore workerB(config);
        const auto a = workerA.claim();
        require(a && a->video_id == "lease-case", "A could not claim the test job");
        query(db.get(), "UPDATE vod_transcode_jobs SET lease_until=UTC_TIMESTAMP()-INTERVAL 1 SECOND "
                        "WHERE video_id='lease-case'");
        const auto b = workerB.claim();
        require(b && b->video_id == a->video_id && a->claim_id != b->claim_id,
                "B did not reclaim the same job with a fresh claim ID");

        constexpr auto snapshot = "SELECT j.status,j.claim_id,j.attempts,j.lease_until,v.status,"
                                  "v.playlist_file_id,v.completed_claim_id FROM vod_transcode_jobs j "
                                  "JOIN vod_videos v USING (video_id) WHERE video_id='lease-case'";
        const auto before = readRow(db.get(), snapshot);
        require(before[0] == "1" && before[1] == b->claim_id && before[2] == "2" &&
                before[3] != "<NULL>" && before[4] == "5", "B's running state was not stored");
        workerA.fail(*a);
        require(readRow(db.get(), snapshot) == before, "A's failure changed B's state");
        workerB.add_artifact(*b, "lease/b-playlist");
        require(!workerA.complete(*a, "lease/b-playlist"), "A's completion was accepted");
        require(readRow(db.get(), snapshot) == before, "A's completion changed B's state");

        require(workerB.complete(*b, "lease/b-playlist"), "B's completion was rejected");
        const auto after = readRow(db.get(), snapshot);
        require(after[0] == "2" && after[1] == b->claim_id && after[2] == "2" &&
                after[3] == "<NULL>" && after[4] == "1" && after[5] == "lease/b-playlist" &&
                after[6] == b->claim_id, "B's result was not stored correctly");
        query(db.get(), "DELETE FROM vod_transcode_artifacts WHERE video_id='lease-case'");
        query(db.get(), "DELETE FROM vod_transcode_jobs WHERE video_id='lease-case'");
        query(db.get(), "DELETE FROM vod_videos WHERE video_id='lease-case'");
        query(db.get(), "DELETE FROM vod_files WHERE file_id='lease/b-playlist'");
        std::cout << "lease reclaim PASS: same video; different claim IDs; attempts=2; "
                     "A fail left B unchanged; A complete=false; B complete=true; "
                     "job 1->2, video 5->1, completed_claim_id=B\n";
    } catch (const std::exception& error) {
        std::cerr << "lease reclaim FAIL: " << error.what() << '\n';
        return 1;
    }
}
