"""PostgreSQL temporary-table demonstration. Requires psycopg 3.

This is an assistant-prepared experiment, not a student implementation.
No production tables or credentials are stored in this file.
"""
import os
import psycopg


def main():
    dsn = os.environ.get('PRACTICE_PG_DSN',
                         'host=127.0.0.1 port=55432 user=docqa dbname=devdocqa_demo')
    with psycopg.connect(dsn, connect_timeout=3, autocommit=True) as connection:
        connection.execute('CREATE TEMP TABLE practice_jobs (id TEXT PRIMARY KEY, status TEXT NOT NULL)')
        connection.execute('CREATE TEMP TABLE practice_request_keys '
                           '(idempotency_key TEXT PRIMARY KEY, job_id TEXT NOT NULL)')
        with connection.transaction():
            connection.execute("INSERT INTO practice_jobs VALUES ('J1','queued')")
            connection.execute("INSERT INTO practice_request_keys VALUES ('K1','J1')")
        print('Initial transaction committed: J1 and K1 -> J1')

        conflict_seen = False
        try:
            # Enter: BEGIN. Normal exit: COMMIT. Exception exit: ROLLBACK.
            with connection.transaction():
                connection.execute("INSERT INTO practice_jobs VALUES ('J2','queued')")
                print('First INSERT succeeded inside the transaction: J2 (not committed)')
                connection.execute("INSERT INTO practice_request_keys VALUES ('K1','J2')")
        except psycopg.errors.UniqueViolation as error:
            conflict_seen = True
            print('Second INSERT failed: duplicate K1; SQLSTATE=' + error.sqlstate)
            print('Transaction context performed ROLLBACK before this handler')

        rows = connection.execute('SELECT id, status FROM practice_jobs ORDER BY id').fetchall()
        keys = connection.execute('SELECT idempotency_key, job_id FROM practice_request_keys').fetchall()
        print('Remaining jobs:', rows)
        print('Remaining keys:', keys)
        if not conflict_seen or rows != [('J1', 'queued')] or keys != [('K1', 'J1')]:
            raise RuntimeError('Unexpected transaction outcome')
        print('PASS: J2 removed; previously committed J1 and K1 preserved')
    print('Connection closed; temporary tables cleaned up')


if __name__ == '__main__':
    main()
