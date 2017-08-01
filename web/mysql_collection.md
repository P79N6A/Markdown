## set mysql default utf8 ##

### set default encode utf8 in /etc/mysql.my ###
`[client]`

default-character-set=utf8

`[[mysqld]]`

default-storage-engine=INNODB
character-set-server=utf8
collation-server=utf8_general_ci

### create database ###

the create database operate must after setting default encode, otherwise, the `character_set_database` will be encode before settings.

### show encode ###

show variables like "char%"

##  启动、停止、重启 MySQL 常见的操作方法(<a href="http://blog.csdn.net/aeolus_pu/article/details/9300205">转载</a>) ##

### 一、启动方式 ###

1、使用 service 启动：service mysqld start

2、使用 mysqld 脚本启动：/etc/inint.d/mysqld start

3、使用 mysqld_safe 启动：mysqld_safe &

### 二、停止 ###
 
1、使用 service 启动：service mysqld stop

2、使用 mysqld 脚本启动：/etc/inint.d/mysqld stop

3、mysqladmin shutdown

### 三、重启 ###

1、使用 service 启动：service mysqld restart

2、使用 mysqld  脚本启动：/etc/inint.d/mysqld restart

官方推荐使用mysqld_safe，使用mysqld_safe启动，会监控mysql进程，如果mysql进程关闭，自动重启mysql进程。

