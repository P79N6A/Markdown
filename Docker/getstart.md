## Orientation ##

- List Docker CLI commands

        docker
        docker container --help
        
- Display Docker version and info

        docker --version
        docker version
        docker info
        
- Excecute Docker image

        docker run hello-world
        
- List Docker images

        docker image ls
       
- List Docker containers(running, all, all in quiet mode)

        docker container ls
        docker container ls -all
        docker container ls -a -q

## Container ##

- Build the app

        docker build -t friendlyhello
       
- Run the app

        docker run -p 4000:80 friendlyhello
        
- Log in with your Docker ID

        docker login
       
- Tag the image

        docker tag image username/repository:tag
        
    For example:
        
        docker tag friendlyhello john/get-started:part2
        
- Publish the image

    upload your tagged image to the repository
        
        docker push username/repository:tag
        
        
- pull and run the image from the remote repository

        docker run -p 4000:80 username/repository:tag
        
        
- a list of the basic Docker command

        docker build -t friendlyhello .  # Create image using this directory's Dockerfile
        docker run -p 4000:80 friendlyhello  # Run "friendlyname" mapping port 4000 to 80
        docker run -d -p 4000:80 friendlyhello         # Same thing, but in detached mode
        docker container ls                                # List all running containers
        docker container ls -a             # List all containers, even those not running
        docker container stop <hash>           # Gracefully stop the specified container
        docker container kill <hash>         # Force shutdown of the specified container
        docker container rm <hash>        # Remove specified container from this machine
        docker container rm $(docker container ls -a -q)         # Remove all containers
        docker image ls -a                             # List all images on this machine
        docker image rm <image id>            # Remove specified image from this machine
        docker image rm $(docker image ls -a -q)   # Remove all images from this machine
        docker login             # Log in this CLI session using your Docker credentials
        docker tag <image> username/repository:tag  # Tag <image> for upload to registry
        docker push username/repository:tag            # Upload tagged image to registry
        docker run username/repository:tag                   # Run image from a registry
        
## Services ##

In part 3, we scale our application and enable load-balancing. To do this, we must go one level up in the hierarchy of a distributed application: the service.

- pip install docker-compose, and create a docker-compose.yml

        version: "3"
        services:
          web:
            # replace username/repo:tag with your name and image details
            image: username/repo:tag
            deploy:
              replicas: 5
              resources:
                limits:
                  cpus: "0.1"
                  memory: 50M
              restart_policy:
                condition: on-failure
            ports:
              - "80:80"
            networks:
              - webnet
        networks:
          webnet:


- create swarm manager

        docker swarm init
       
- run app in swarm, and give app a name

        docker stack deploy -c docker-compose.yml getstartedlab

- verify

        curl -4 http://127.0.0.1 (here will fail if use localhost, I don't know why it happen)
        
- Scale the app

        You can scale the app by changing the replicas value in docker-compose.yml, saving the change, and re-running the docker stack deploy command:
        
        docker stack deploy -c docker-compose.yml getstartedlab
        
- Take down the app and the swarm

        docker stack rm getstartedlab
        
- Take down the swarm

        docker swarm leave --force
        
- Some commands to explore at this stage:

        docker stack ls                                            #                        List stacks or apps
        # Run the specified Compose file
        docker stack deploy -c <composefile> <appname>  
        
        # List running services
        docker service ls                  associated with an app
        
        # List tasks associated with an app
        docker service ps <service>                  
        
        # Inspect task or container
        docker inspect <task or container>                   
        
        # List container IDs
        docker container ls -q                                      
        
        # Tear down an application
        docker stack rm <appname>                             
        
        # Take down a single node swarm from the manager
        docker swarm leave --force      
        
## Swarms ##     

Here in part4, you deploy this application onto a cluster, running it on multiple machines. Multi-container, multi-machine applications are made possible by joining multiple machines into "Dockerized" cluster called a **swarm**.

#### Understanding Swarm cluster ####

A swarm is a group of machines that are running Docker and joined into a cluster. After that has happened, you continue to run the Docker commands you’re used to, but now they are executed on a cluster by a **swarm manager**. The machines in a swarm can be physical or virtual. After joining a swarm, they are referred to as **nodes**.

Swarm managers can use several strategies to run containers, such as “emptiest node” – which fills the least utilized machines with containers. Or “global”, which ensures that each machine gets exactly one instance of the specified container. You instruct the swarm manager to use these strategies in the Compose file, just like the one you have already been using.

Swarm managers are the only machines in a swarm that can execute your commands, or authorize other machines to join the swarm as **workers**. Workers are just there to provide capacity and do not have the authority to tell any other machine what it can and cannot do.

Up until now, you have been using Docker in a single-host mode on your local machine. But Docker also can be switched into **swarm mode**, and that’s what enables the use of swarms. Enabling swarm mode instantly makes the current machine a swarm manager. From then on, Docker runs the commands you execute on the swarm you’re managing, rather than just on the current machine.

#### Set up your swarm ####

- make your current machine a swarm manager

        docker swarm init

- other machines to have them join the swarm as workers

