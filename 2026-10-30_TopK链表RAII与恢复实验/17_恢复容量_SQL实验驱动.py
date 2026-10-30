"""Assistant-provided isolated SQL driver. Requires psycopg 3 and PostgreSQL.

Only a session temporary table is used. The server is started/stopped separately.
This experiment does not perform an actual backend restart or concurrency test.
"""
import os
from pathlib import Path

import psycopg


def main():
    here = Path(__file__).resolve().parent
    query = (here / '16_恢复容量与排除_SQL.sql').read_text(encoding='utf-8')
    if not query.strip() or all(not line.strip() or line.lstrip().startswith('--') for line in query.splitlines()):
        raise RuntimeError('SQL exercise is still empty.')
    dsn = os.environ.get('PRACTICE_PG_DSN',
                         'host=127.0.0.1 port=55432 user=docqa dbname=devdocqa_demo')
    with psycopg.connect(dsn, connect_timeout=3, autocommit=True) as connection:
        connection.execute('CREATE TEMP TABLE practice_jobs '
                           '(id TEXT PRIMARY KEY, status TEXT NOT NULL, age_seconds INTEGER NOT NULL, created_at TIMESTAMP NOT NULL)')
        connection.execute("INSERT INTO practice_jobs VALUES "
                           "('J1','queued',10,'2026-10-30 12:00:00'),"
                           "('J2','queued',120,'2026-10-30 12:01:00'),"
                           "('J3','failed',15,'2026-10-30 12:02:00'),"
                           "('J4','queued',20,'2026-10-30 12:03:00'),"
                           "('J5','queued',25,'2026-10-30 12:04:00'),"
                           "('J6','queued',30,'2026-10-30 12:05:00')")
        rows = connection.execute(query).fetchall()
        print('Candidate rows:', rows)
        expected = [('J2', 120), ('J5', 25)]
        if rows != expected:
            raise RuntimeError(f'Unexpected rows; expected {expected!r}')
        print('PASS: queued, excluded IDs, order and limit')
    print('Connection closed; temporary table cleaned up')


if __name__ == '__main__':
    main()
