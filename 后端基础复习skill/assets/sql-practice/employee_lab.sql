-- Only run in a dedicated intern_lab database on a local MySQL 8.0 practice instance.
-- This file creates two skill_-prefixed tables and inserts 18 rows.
-- It does not drop or alter existing databases or tables.
-- Run once on a fresh practice database; rerunning the INSERTs causes primary-key errors.
USE intern_lab;

CREATE TABLE IF NOT EXISTS skill_department (
    department_id INT PRIMARY KEY,
    department_name VARCHAR(40) NOT NULL,
    city VARCHAR(40) NOT NULL
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS skill_employee (
    employee_id INT PRIMARY KEY,
    employee_name VARCHAR(40) NOT NULL,
    job_title VARCHAR(40) NOT NULL,
    manager_id INT NULL,
    hired_on DATE NOT NULL,
    salary DECIMAL(9,2) NOT NULL,
    commission DECIMAL(9,2) NULL,
    department_id INT NOT NULL,
    CONSTRAINT fk_skill_employee_department
        FOREIGN KEY (department_id) REFERENCES skill_department(department_id)
) ENGINE=InnoDB;

INSERT INTO skill_department (department_id, department_name, city) VALUES
    (10, 'ACCOUNTING', 'NEW YORK'),
    (20, 'RESEARCH', 'DALLAS'),
    (30, 'SALES', 'CHICAGO'),
    (40, 'OPERATIONS', 'BOSTON');

INSERT INTO skill_employee
    (employee_id, employee_name, job_title, manager_id, hired_on, salary, commission, department_id)
VALUES
    (7369, 'SMITH',  'CLERK',     7902, '1980-12-17',  800.00, NULL,    20),
    (7499, 'ALLEN',  'SALESMAN',  7698, '1981-02-20', 1600.00,  300.00, 30),
    (7521, 'WARD',   'SALESMAN',  7698, '1981-02-22', 1250.00,  500.00, 30),
    (7566, 'JONES',  'MANAGER',   7839, '1981-04-02', 2975.00, NULL,    20),
    (7654, 'MARTIN', 'SALESMAN',  7698, '1981-09-28', 1250.00, 1400.00, 30),
    (7698, 'BLAKE',  'MANAGER',   7839, '1981-05-01', 2850.00, NULL,    30),
    (7782, 'CLARK',  'MANAGER',   7839, '1981-06-09', 2450.00, NULL,    10),
    (7788, 'SCOTT',  'ANALYST',   7566, '1987-04-19', 3000.00, NULL,    20),
    (7839, 'KING',   'PRESIDENT', NULL, '1981-11-17', 5000.00, NULL,    10),
    (7844, 'TURNER', 'SALESMAN',  7698, '1981-09-08', 1500.00,    0.00, 30),
    (7876, 'ADAMS',  'CLERK',     7788, '1987-05-23', 1100.00, NULL,    20),
    (7900, 'JAMES',  'CLERK',     7698, '1981-12-03',  950.00, NULL,    30),
    (7902, 'FORD',   'ANALYST',   7566, '1981-12-03', 3000.00, NULL,    20),
    (7934, 'MILLER', 'CLERK',     7782, '1982-01-23', 1300.00, NULL,    10);
