# MySQL 独立练习：连接、聚合、子查询

这份练习改编自课件附带的 `scott_data.sql` 和两页《MySQL 课堂实践》。原始补充脚本有删除数据库的语句，索引脚本还尝试生成 800 万行；**不要直接在现有实例上运行它们**。本 Skill 提供的小数据集只在 `intern_lab` 中新增 `skill_` 前缀的表，不触碰 DevDocQA 使用的 PostgreSQL。先完成 [环境搭建](environment.md)。

## 加载与核对

在 MySQL 8.0 练习实例中，只运行一次 [employee_lab.sql](../assets/sql-practice/employee_lab.sql)。若使用 Ubuntu Bash，从 Skill 根目录执行：

```bash
mysql -u intern_lab -p intern_lab < assets/sql-practice/employee_lab.sql
```

密码由交互提示输入，不写进命令或仓库。脚本不执行 `DROP`，但重复运行会因主键重复而报错；若已经加载，直接验证数据，不要反复导入。

```sql
USE intern_lab;
SELECT COUNT(*) AS department_count FROM skill_department; -- 应为 4
SELECT COUNT(*) AS employee_count FROM skill_employee; -- 应为 14
```

这些预期值根据随附脚本的静态数据计算；若实测不同，先停下检查是否运行在预期数据库中。

## 练习题

每题先自己写 SQL，再看提示；请解释 `JOIN` 的基表、连接条件、过滤条件和结果行数。

1. 列出每个部门名称及员工数，**没有员工的部门也要保留**。预期部门 10/20/30/40 的人数为 3/5/6/0。提示：从 `skill_department` 出发做 `LEFT JOIN`，用 `COUNT(e.employee_id)`。
2. 找出与 `FORD` 同部门、但不包含 `FORD` 本人的员工姓名。预期为 `SMITH`、`JONES`、`SCOTT`、`ADAMS`。提示：子查询先求 `FORD` 的 `department_id`。
3. 找出工资高于**自己所在部门平均工资**的员工。预期共 6 人。提示：相关子查询的部门条件要引用外层员工所在部门，不能拿全公司平均值比较。
4. 找出员工及其直属经理的姓名；没有经理的 `KING` 是否出现？提示：员工表与自身按 `manager_id = employee_id` 连接。分别用内连接与左连接观察区别。

第 2 题利用这份固定样本中 `FORD` 姓名唯一的事实；表结构并未约束姓名唯一。真实业务查询应优先用稳定的员工 ID 定位，不能默认同名员工不存在。

## 参考 SQL 与复盘

做完再展开思路，不能只抄结果。把自己的 SQL、实际结果、错误原因记在练习日志里。

```sql
-- 1. 没有员工的部门仍保留；COUNT(e.employee_id) 不会把右表的 NULL 行计入。
SELECT d.department_id, d.department_name, COUNT(e.employee_id) AS employee_count
FROM skill_department AS d
LEFT JOIN skill_employee AS e ON e.department_id = d.department_id
GROUP BY d.department_id, d.department_name
ORDER BY d.department_id;

-- 2. 子查询定位 FORD 所在部门。
SELECT e.employee_name
FROM skill_employee AS e
WHERE e.department_id = (
    SELECT department_id FROM skill_employee WHERE employee_name = 'FORD'
)
  AND e.employee_name <> 'FORD'
ORDER BY e.employee_id;

-- 3. 外层每名员工分别与本部门的平均工资比较。
SELECT e.employee_name, e.salary, e.department_id
FROM skill_employee AS e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM skill_employee AS e2
    WHERE e2.department_id = e.department_id
)
ORDER BY e.employee_id;

-- 4. 用 LEFT JOIN 保留没有经理的 KING；INNER JOIN 则不保留。
SELECT e.employee_name, m.employee_name AS manager_name
FROM skill_employee AS e
LEFT JOIN skill_employee AS m ON m.employee_id = e.manager_id
ORDER BY e.employee_id;
```

面试追问：第 1 题把 `COUNT(e.employee_id)` 改成 `COUNT(*)` 会怎样？第 3 题的相关子查询每行都重算吗，优化器可能如何改写？第 4 题为什么不能把员工和经理都按 `department_id` 连接？后两问需要结合执行计划和数据关系回答，别从 SQL 表面臆测执行次数。
