## 简单介绍

- MySQL（关系型数据库）

	- 持久化存储数据
	- 安装（MySQL 管理员密码：root）
		- 数据库的进程会监听 3306 端口（区分一台机器中不同的进程，每个进程占用不同的 PORT（端口））
			- MySQL 安装是同时安装了客户端（有命令行式客户端、图形界面客户端）和服务端
			- 客户端通过 IP + PORT 对服务端进行操作
		- 服务端：mysqld
		- 客户端：mysql

- 基本概念

	- 表：有行（记录）、有列（字段）
		- 记录：一条数据
		- 一列：就是一个字段
	- 库：一个库中有 多张表

- 数据链接

	- 命令行客户端

		- | 命令                                 | 说明                                                         |
			| ------------------------------------ | ------------------------------------------------------------ |
			| `mysql -uroot -p`                    | 连接本机 MySQL（默认 [localhost: 3306](https://localhost:3306/)），回车后输入密码 |
			| `mysql -hlocalhost -P3306 -uroot -p` | 完整格式连接本机 MySQL，指定主机与端口                       |
			| `mysql -hIP地址 -P3306 -uroot -p`    | 连接其他主机上的 MySQL 服务                                  |

	- 图形客户端：navicat、sqlyog

## 库相关操作

- | 命令                    | 说明           | 通用示例                |
	| ----------------------- | -------------- | ----------------------- |
	| `create database 库名;` | 创建数据库     | `create database mydb;` |
	| `drop database 库名;`   | 删除数据库     | `drop database mydb;`   |
	| `show databases;`       | 查看所有数据库 | `show databases;`       |

## 表相关

- 

- | 命令                                            | 说明               | 通用示例                                                     |
	| ----------------------------------------------- | ------------------ | ------------------------------------------------------------ |
	| `use 库名;`                                     | 进入 / 切换数据库  | `use mydb;`                                                  |
	| `create table 表名(字段1 类型, 字段2 类型...);` | 创建表             | `create table t_user(id int, name varchar(20), age int, money decimal(10,2), create_time datetime);` |
	| `drop table 表名;`                              | 删除表             | `drop table t_user;`                                         |
	| `show tables;`                                  | 查看当前库下所有表 | `show tables;`                                               |

## 数据操作

### 单张表

- 

- | 命令                                                         | 说明         | 通用示例                                                     |
	| ------------------------------------------------------------ | ------------ | ------------------------------------------------------------ |
	| `insert into 表名(字段1,字段2...) values(值1,值2...);`       | 添加数据     | `insert into t_user(id,name,age) values(1,'张三',20);`       |
	| `update 表名 set 字段1=值1,字段2=值2 where 主键=值;`         | 修改数据     | `update t_user set name='李四',age=21 where id=1;`           |
	| `delete from 表名 where 主键=值;`                            | 删除单条数据 | `delete from t_user where id=1;`                             |
	| `delete from 表名;`                                          | 删除全部数据 | `delete from t_user;`                                        |
	| `select * from 表名;`                                        | 查询所有字段 | `select * from t_user;`                                      |
	| `select * from 表名 where 字段1=x and 字段2=y;`              | 多条件且查询 | `select * from t_user where id=1 and age=20;`                |
	| `select * from 表名 where 字段1=x or 字段2=y;`               | 多条件或查询 | `select * from t_user where id=1 or age=20;`                 |
	| `select * from 表名 where 字段>=x;`                          | 比较条件查询 | `select * from t_user where age>=18;`                        |
	| `alter table 表名 add primary key(字段);`                    | 设置主键     | `alter table t_user add primary key(id);`                    |
	| `alter table 表名 add 字段名 类型 [约束];`                   | 添加字段     | `alter table t_user add phone varchar(11);`                  |
	| `alter table 表名 change 旧名 新名 类型 [约束];`             | 修改字段名   | `alter table t_user change name username varchar(20);`       |
	| `alter table 子表 add constraint 外键名 foreign key(外键列) references 父表(主键列);` | 设置外键     | `alter table t_order add constraint fk_user_id foreign key(user_id) references t_user(id);` |

### 两张表

- 判断两张表的关系：站在双向来讲

	- 例如： 学生 和 班级  ===> 1: N
		- 站在学生角度：1 个学生 对应 1 个班级  ==> 1:1
		- 站在班级的角度：1 个班 对应 多个学生 ==> 1：N
	- **一对多关系表设计**：在 多的一方(学生)  拥有 一的一方(班级)  的外键
		- 主键：唯一能区分这行记录 和 其他记录的字段
		- 外键：为了保证数据的完整性，引用其他表的一个字段

- 

- | 命令                                                    | 说明               | 通用示例                                                     |
	| ------------------------------------------------------- | ------------------ | ------------------------------------------------------------ |
	| `select 字段1,字段2... from 表名;`                      | 查询指定字段       | `select id,name from t_user;`                                |
	| `select * from 表名 where 字段1=值1 and 字段2=值2;`     | 多条件精确查询     | `select * from t_user where age=20 and sex='男';`            |
	| `select count(*) from 表名;`                            | 查询表中数据总行数 | `select count(*) from emp;`                                  |
	| `select 展示字段 from 表1,表2 where 表1.字段=表2.字段;` | 多表关联查询       | `select * from t_user,t_order where t_user.id=t_order.user_id;` |

