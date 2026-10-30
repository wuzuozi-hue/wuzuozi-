"""Assistant-provided adapter: real PostgreSQL temporary table -> C++ exercise.

Requires psycopg 3, an available local test PostgreSQL and a compiled C++
exercise executable passed as argv[1]. It does not restart the real backend,
modify production tables or persist failed status.
"""
import os
from pathlib import Path
import subprocess
import sys

import psycopg

HERE = Path(__file__).resolve().parent
SQL = HERE / '13_恢复串联_候选查询.sql'


def run_scenario(executable, rows, loaded, pending):
    lines = [f'120 {len(rows)}']
    lines.extend(f'{job_id} {age}' for job_id, age in rows)
    lines.append(' '.join([str(len(loaded)), *sorted(loaded)]))
    lines.append(' '.join([str(len(pending)), *sorted(pending)]))
    result = subprocess.run([str(executable)], input='\n'.join(lines) + '\n',
                            capture_output=True, text=True, encoding='utf-8', timeout=10)
    if result.returncode != 0:
        raise RuntimeError(f'C++ exercise exited {result.returncode}: {result.stderr.strip()}')
    return result.stdout.strip().splitlines()


def main():
    if len(sys.argv) != 2:
        raise SystemExit('Provide the compiled C++ exercise executable or --sql-only.')
    sql_only = sys.argv[1] == '--sql-only'
    executable = None if sql_only else Path(sys.argv[1]).resolve()
    query = SQL.read_text(encoding='utf-8')
    if not query.strip() or all(not line.strip() or line.lstrip().startswith('--') for line in query.splitlines()):
        raise RuntimeError('SQL exercise is still empty.')
    dsn = os.environ.get('PRACTICE_PG_DSN',
                         'host=127.0.0.1 port=55432 user=docqa dbname=devdocqa_demo')
    with psycopg.connect(dsn, connect_timeout=3, autocommit=True) as connection:
        connection.execute('CREATE TEMP TABLE practice_jobs '
                           '(id TEXT PRIMARY KEY, status TEXT NOT NULL, age_seconds INTEGER NOT NULL, created_at TIMESTAMP NOT NULL)')
        connection.execute("INSERT INTO practice_jobs VALUES "
                           "('J2','queued',120,'2026-10-30 12:00:00'),"
                           "('J1','queued',10,'2026-10-30 12:00:00'),"
                           "('J3','failed',15,'2026-10-30 12:01:00'),"
                           "('J4','queued',20,'2026-10-30 12:03:00')")
        rows = connection.execute(query).fetchall()
        expected_rows = [('J1', 10), ('J2', 120), ('J4', 20)]
        if rows != expected_rows:
            raise RuntimeError(f'SQL candidate rows incorrect: {rows!r}; expected {expected_rows!r}')
        print('SQL candidates: J1/10, J2/120, J4/20')
        if sql_only:
            print('PASS: SQL ordering and filtering; temporary table removed on disconnect')
            return
        scenarios = [
            ('already loaded/pending', {'J1'}, {'J4'}, ['READY', 'EXPIRED J2']),
            ('simulated restart, sets empty', set(), set(), ['READY J1 J4', 'EXPIRED J2']),
            ('J4 loaded', {'J4'}, set(), ['READY J1', 'EXPIRED J2']),
        ]
        for label, loaded, pending, expected in scenarios:
            actual = run_scenario(executable, rows, loaded, pending)
            if actual != expected:
                raise RuntimeError(f'{label}: actual {actual!r}; expected {expected!r}')
            print(f'{label}: PASS; ' + ' | '.join(actual))
    print('PASS: SQL ordering and all 3 C++ scenarios; temporary table removed on disconnect')


if __name__ == '__main__':
    main()
