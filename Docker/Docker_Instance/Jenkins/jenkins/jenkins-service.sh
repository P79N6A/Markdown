#!/bin/bash

#create swarm network
docker network create -d overlay jenkins_master_net

#create visualizer docker
docker service create --name visualizer --mount type=bind,source=/var/run/docker.sock,destination=/var/run/docker.sock --constraint 'node.role==manager' --network jenkins_master_net --publish 8000:8080 dockersamples/visualizer:stable

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

