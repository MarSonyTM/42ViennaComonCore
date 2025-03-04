# Inception Project Evaluation Guide

This guide provides explanations and testing commands for each point in the Inception project evaluation.

## Preliminaries

### Checking for Cheating
- Carefully review the code to ensure it's original work
- Look for signs of copied code or unauthorized use of pre-made solutions

### Preliminary Tests
- Ensure the evaluated student is present for the defense
- Verify that all required files have been submitted
- Clone their Git repository on their station:
  ```bash
  git clone git@vogsphere.msk.21-school.ru:vogsphere/intra-uuid-580658e
  ```

## General Instructions

### Repository Structure
- Check that all configuration files are in a `srcs` folder at the root of the repository:
  ```bash
  ls -la
  ls -la srcs/
  ```
- Verify a Makefile exists at the root:
  ```bash
  ls -la | grep Makefile
  ```

### Docker Environment Cleanup
- Run this command to clean up Docker environment before starting:
  ```bash
  docker stop $(docker ps -qa); docker rm $(docker ps -qa); docker rmi -f $(docker images -qa); docker volume rm $(docker volume ls -q); docker network rm $(docker network ls -q) 2>/dev/null
  ```

### Docker Compose Configuration
- Check the docker-compose.yml file for prohibited configurations:
  ```bash
  cat srcs/docker-compose.yml | grep -E "network: host|links:"
  ```
  (Should return nothing)
- Verify networks are defined:
  ```bash
  cat srcs/docker-compose.yml | grep -E "networks?:"
  ```
  (Should find network definitions)

### Docker Configuration
- Check Makefile and scripts for prohibited '--link' option:
  ```bash
  grep -r "\-\-link" .
  ```
  (Should return nothing)
- Examine Dockerfiles for prohibited background commands:
  ```bash
  grep -r "tail -f" .
  grep -r "ENTRYPOINT.*bash\|sh" .
  ```
- Check scripts for infinite loops:
  ```bash
  grep -r "sleep infinity\|tail -f /dev/null\|tail -f /dev/random" .
  ```

### Run the Makefile
- Execute the Makefile to build and start the containers:
  ```bash
  make
  ```

## Mandatory Part

### Project Overview

#### Docker and docker-compose explanation
The student should explain:
- Docker is a platform that uses containerization to package applications and their dependencies
- Containers are lightweight, isolated environments that share the host OS kernel
- docker-compose is a tool for defining and running multi-container Docker applications
- It uses a YAML file to configure application services, networks, and volumes
- With a single command, it creates and starts all services from the configuration

#### Docker image with vs. without docker-compose explanation
The student should explain:
- Without docker-compose: Images are built and containers are run individually with docker commands
- With docker-compose: Images are defined in a docker-compose.yml file and built/run together
- docker-compose manages networking between containers automatically
- docker-compose simplifies environment variables and volume management
- docker-compose makes it easier to define relationships between services

#### Benefits of Docker vs. VMs explanation
The student should explain:
- Docker containers share the host OS kernel, making them more lightweight
- Containers start up in seconds vs. minutes for VMs
- Docker uses less resources (CPU, memory, storage) than VMs
- Docker provides better consistency across different environments
- Docker enables easier scaling and deployment of applications

#### Directory structure explanation
The student should explain:
- The structure separates configuration files (in srcs/) from build instructions (Makefile)
- Each service has its own directory with its Dockerfile and configuration
- This organization makes the project more maintainable and easier to understand
- The structure follows the principle of separation of concerns

### Simple Setup

#### NGINX Access and SSL/TLS
- Test NGINX is only accessible via HTTPS (port 443):
  ```bash
  curl -I http://login.42.fr
  ```
  (Should fail or redirect)
  ```bash
  curl -I -k https://login.42.fr
  ```
  (Should succeed with 200 OK)

- Verify SSL/TLS certificate:
  ```bash
  openssl s_client -connect login.42.fr:443
  ```
  (Should show certificate information)

- Check WordPress installation:
  Open https://login.42.fr in browser
  (Should see WordPress site, not installation page)

### Docker Basics

#### Dockerfile Check
- Verify each service has its own Dockerfile:
  ```bash
  ls -la srcs/*/Dockerfile
  ```
- Check Dockerfiles are not empty:
  ```bash
  for file in $(find srcs -name "Dockerfile"); do echo "$file:"; cat "$file"; echo; done
  ```

#### Base Image Check
- Verify Dockerfiles use Alpine or Debian Buster:
  ```bash
  grep -r "^FROM" srcs/
  ```
  (Should show FROM alpine or FROM debian:buster)

#### Image Names
- Check Docker images have same names as services:
  ```bash
  docker-compose config --services
  docker images
  ```
  (Compare the lists)

#### Makefile Setup
- Verify Makefile sets up all services via docker-compose:
  ```bash
  cat Makefile
  docker-compose ps
  ```
  (All services should be running)

### Docker Network

#### Network Configuration
- Check docker-compose.yml for network configuration:
  ```bash
  cat srcs/docker-compose.yml | grep -A 10 "networks:"
  ```
- Verify network exists:
  ```bash
  docker network ls
  ```

#### Docker Network Explanation
The student should explain:
- Docker networks allow containers to communicate with each other
- They provide isolation from other networks
- They enable DNS resolution between containers
- They can be customized with different drivers for different needs
- They eliminate the need for linking containers manually

### NGINX with SSL/TLS

#### NGINX Dockerfile
- Verify NGINX Dockerfile exists:
  ```bash
  ls -la srcs/nginx/Dockerfile
  ```

#### Container Creation
- Check NGINX container is running:
  ```bash
  docker-compose ps | grep nginx
  ```

#### HTTP Access Test
- Verify HTTP access is blocked:
  ```bash
  curl -I http://login.42.fr
  ```
  (Should fail or redirect)

#### HTTPS Access Test
- Open https://login.42.fr in browser
  (Should display WordPress site)

#### TLS Certificate
- Verify TLS certificate:
  ```bash
  openssl s_client -connect login.42.fr:443 | grep "Protocol"
  ```
  (Should show TLSv1.2 or TLSv1.3)

### WordPress with php-fpm and its volume

#### WordPress Dockerfile
- Verify WordPress Dockerfile exists:
  ```bash
  ls -la srcs/wordpress/Dockerfile
  ```
- Check it doesn't contain NGINX:
  ```bash
  grep -i "nginx" srcs/wordpress/Dockerfile
  ```
  (Should return nothing)

#### Container Creation
- Check WordPress container is running:
  ```bash
  docker-compose ps | grep wordpress
  ```

#### Volume Check
- Verify WordPress volume exists:
  ```bash
  docker volume ls
  docker volume inspect <wordpress_volume_name>
  ```
  (Should show path /home/login/data/)

#### WordPress Functionality
- Test adding a comment on the WordPress site
- Sign in with admin account (username should not contain 'admin' or 'Admin')
- Edit a page and verify changes appear on the site

### MariaDB and its volume

#### MariaDB Dockerfile
- Verify MariaDB Dockerfile exists:
  ```bash
  ls -la srcs/mariadb/Dockerfile
  ```
- Check it doesn't contain NGINX:
  ```bash
  grep -i "nginx" srcs/mariadb/Dockerfile
  ```
  (Should return nothing)

#### Container Creation
- Check MariaDB container is running:
  ```bash
  docker-compose ps | grep mariadb
  ```

#### Volume Check
- Verify MariaDB volume exists:
  ```bash
  docker volume ls
  docker volume inspect <mariadb_volume_name>
  ```
  (Should show path /home/login/data/)

#### Database Login
- The student should explain how to login to the database
- Test root login without password (should fail):
  ```bash
  docker exec -it <mariadb_container_name> mysql -u root
  ```
- Test user login with password:
  ```bash
  docker exec -it <mariadb_container_name> mysql -u <username> -p
  ```
  (Enter password when prompted)
- Verify database is not empty:
  ```sql
  SHOW DATABASES;
  USE wordpress;
  SHOW TABLES;
  ```

### Persistence

#### Reboot Test
- Reboot the virtual machine:
  ```bash
  sudo reboot
  ```
- After reboot, start services again:
  ```bash
  make
  ```
- Verify WordPress site still works with previous changes
- Verify database data is still present:
  ```bash
  docker exec -it <mariadb_container_name> mysql -u <username> -p
  ```
  (Enter password when prompted)
  ```sql
  SHOW DATABASES;
  USE wordpress;
  SHOW TABLES;
  ```

## Bonus

For each bonus service:
1. Verify it has a proper Dockerfile
2. Check the container is running
3. Test the functionality of the service
4. For the free choice service, the student should explain:
   - How it works
   - Why it's useful for the infrastructure

Rate each bonus from 0-5 based on implementation quality and usefulness. 