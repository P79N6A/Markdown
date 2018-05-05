#!/bin/bash

#-----------Normal----------#


#create swarm network
docker network create -d overlay jenkins_master_net

#--virsualizer--#
#create visualizer docker
docker service create --name visualizer --mount type=bind,source=/var/run/docker.sock,destination=/var/run/docker.sock --constraint 'node.role==manager' --network jenkins_master_net --publish 8000:8080 dockersamples/visualizer:stable

#--jenkins_master--#
#create jenkins_master docker
docker service create --user root --name jenkins_master --mount type=bind,source=/var/jenkins_home,destination=/var/jenkins_home --constraint 'node.role==worker' --restart-condition='on-failure'  --network jenkins_master_net --publish 36093:36093 --publish 8080:8080 damoncheng/public:jenkins

#create jenkins_master docker by bind and volumn
docker service create --user root --name jenkins_master --mount type=bind,source=/home/damoncheng,destination=/home/damoncheng --mount type=volume,source=jenkins,destination=/var/jenkins_home --constraint 'node.role==manager' --restart-condition='on-failure'  --network jenkins_master_net --publish 36093:50000 --publish 8080:8080 jenkins/jenkins:lts

#create jenkins blueocean_master docker by bind
docker service create --user root --name jenkins_master --mount type=bind,source=/var/jenkins_home,destination=/var/jenkins_home --constraint 'node.role==worker' --restart-condition='on-failure'  --network jenkins_master_net --publish 36093:50000 --publish 8080:8080 jenkinsci/blueocean

#create jenkins blueocean_master docker by volumn
docker service create --user root --name jenkins_master --mount type=volume,source=jenkins_home,destination=/var/jenkins_home --constraint 'node.role==worker' --restart-condition='on-failure'  --network jenkins_master_net --publish 36093:50000 --publish 8080:8080 damoncheng/public:jenkinsci-blueocean

#create jenkins blueocean_master docker by bind and volumn  
docker service create --user root --name jenkins_master --mount type=bind,source=/home/damoncheng,destination=/home/damoncheng --mount type=volume,source=jenkins_home,destination=/var/jenkins_home --constraint 'node.role==manager' --restart-condition='on-failure' -e JAVA_OPTS=-Duser.timezone=Hongkong --network jenkins_master_net --publish 36093:50000 --publish 8080:8080 damoncheng/public:jenkinsci-blueocean

#create jenkins blueocean_master docker by bind and volumn and timer
  
#我的工作环境
docker service create --user root --name jenkins_master --mount type=bind,source=/tmp,destination=/tmp --mount type=volume,source=jenkins_home,destination=/var/jenkins_home --constraint 'node.role==worker' --restart-condition='on-failure' -e JAVA_OPTS=-Duser.timezone=Hongkong --network jenkins_master_net --publish 36093:50000 --publish 8080:8080 damoncheng/jenkins:blueocean-timer

#正式环境部署
docker service create --user root --name jenkins_master --mount type=bind,source=/tmp,destination=/tmp --mount type=volume,source=jenkins_home,destination=/var/jenkins_home --constraint 'node.role==worker' --restart-condition='on-failure' -e JAVA_OPTS=-Duser.timezone=Hongkong --publish 36093:50000 --publish 8080:8080 damoncheng/jenkins:blueocean-timer


#create jenkins blueocean_master docker by bind and bind and timer
docker service create --user root --name jenkins_master --mount type=bind,source=/tmp,destination=/tmp --mount type=bind,source=/var/jenkins_home,destination=/var/jenkins_home --constraint 'node.role==manager' --restart-condition='on-failure' -e JAVA_OPTS=-Duser.timezone=Hongkong --network jenkins_master_net --publish 36093:50000 --publish 8080:8080 damoncheng/jenkins:blueocean-timer


#--rsync and inotify--#

#正式部署环境
docker service create --user root -e "IP_LIST=`cat ip.list`" --name jenkins_master_storage --mount type=bind,source=/tmp,destination=/tmp --mount type=volume,source=jenkins_home,destination=/var/jenkins_home --constraint 'node.role==worker' --mode global --restart-condition='on-failure' --publish 873:873  damoncheng/jenkins:sync-2

#我的工作环境 挂载jenkins deploy
docker service create --user root -e "IP_LIST=`cat ip.list`" --name jenkins_master_storage --mount type=bind,source=/tmp,destination=/tmp \
                      --mount type=volume,source=jenkins_deploy,destination=/jenkins_deploy \
                      --mount type=volume,source=jenkins_home,destination=/var/jenkins_home \
                      --mode global --restart-condition='on-failure' --publish 873:873  damoncheng/jenkins:sync-v3


#-------------Test-----------#
#create jenkins blueocean_master docker by bind and add a timer
docker service create --user root --name jenkins_master --mount type=bind,source=/tmp,destination=/tmp --mount type=volume,source=jenkins_home_timer,destination=/var/jenkins_home --constraint 'node.role==worker' --restart-condition='on-failure' -e JAVA_OPTS=-Duser.timezone=Hongkong --network jenkins_master_net --publish 36093:50000 --publish 8080:8080 damoncheng/jenkins:blueocean-timer


docker service create --user root -e "IP_LIST=`cat ip.list`" --name jenkins_master_storage --mount type=bind,source=/tmp,destination=/tmp --mount type=volume,source=jenkins_home_timer,destination=/var/jenkins_home --constraint 'node.role==worker' --mode global --restart-condition='on-failure' --publish 873:873  damoncheng/test:rsyncd


docker --user root -e "IP_LIST=`cat ip.list`"  run damoncheng/test:rsyncd


