# Use an official Python runtime as a parent image
FROM launcher.gcr.io/google/debian8:latest

# Install any needed packages specified in requirements.txt
RUN apt-get update && apt-get install -y inotify-tools rsync

# Set the working directory to /app
WORKDIR /home/damoncheng/Git/Markdown/Docker/Docker_Instance/Cluster_Master

# Copy the current directory contents into the container at /app
ADD . /home/damoncheng/Git/Markdown/Docker/Docker_Instance/Cluster_Master
ADD ./rsyncd.secrets /etc/rsyncd.secrets

# Make port 80 available to the world outside this container
# EXPOSE 873 873

# Run app.py when the container launches
# CMD ["./run_cluster.sh"]

