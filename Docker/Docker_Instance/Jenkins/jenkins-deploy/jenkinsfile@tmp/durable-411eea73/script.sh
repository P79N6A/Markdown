#!/bin/sh -xe
rsync -rvlHpogDtSu --delete --password-file=/home/docker/rsyncd.secrets ../ root@192.168.99.1::jenkins_deploy