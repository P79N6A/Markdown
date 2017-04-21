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