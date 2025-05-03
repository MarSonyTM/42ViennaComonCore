# Inception Project: Student Explanation Guide

This document contains the key topics you need to be able to explain during your Inception project evaluation, along with detailed explanations to help you prepare.

Inception Project Overview
Inception is a Docker-based infrastructure project that sets up a complete web application stack with three main services:
1.NGINX - Web server with SSL termination
2.WordPress - PHP-based content management system
3.MariaDB - MySQL-compatible database server

## Project Overview

### 1. How Docker and docker-compose work

**Explanation:**
- **Docker** is a containerization platform that packages applications and their dependencies into isolated containers. It uses a client-server architecture where the Docker daemon (server) manages containers, and the Docker CLI (client) sends commands to the daemon.
- Docker creates containers using images, which are read-only templates containing the application code, libraries, dependencies, and tools needed to run an application.
- **Docker-compose** is a tool for defining and running multi-container Docker applications. It uses a YAML file to configure all the application's services, networks, and volumes in one place, then creates and starts all the containers with a single command.
- Docker-compose simplifies the process of managing multiple containers that need to work together, handling networking between them automatically.

### 2. The difference between a Docker image used with docker-compose and without docker-compose

**Explanation:**
- **Without docker-compose**: You manage each container individually using `docker run` commands with many parameters. You need to manually create networks, set up volumes, and ensure containers start in the correct order. Configuration is spread across multiple command lines or scripts.
  ```bash
  docker network create my_network
  docker run -d --name mariadb --network my_network -v /path/to/data:/var/lib/mysql mariadb:latest
  docker run -d --name wordpress --network my_network -v /path/to/wp:/var/www/html wordpress:latest
  docker run -d --name nginx --network my_network -p 443:443 -v /path/to/wp:/var/www/html nginx:latest
  ```

- **With docker-compose**: All services are defined in a single YAML file. Docker-compose handles creating networks, volumes, and starting containers in the correct order. It provides a more declarative and maintainable approach.
  ```yaml
  services:
    mariadb:
      image: mariadb:latest
      volumes:
        - /path/to/data:/var/lib/mysql
      networks:
        - my_network
    
    wordpress:
      image: wordpress:latest
      volumes:
        - /path/to/wp:/var/www/html
      networks:
        - my_network
      depends_on:
        - mariadb
    
    nginx:
      image: nginx:latest
      ports:
        - "443:443"
      volumes:
        - /path/to/wp:/var/www/html
      networks:
        - my_network
      depends_on:
        - wordpress
  
  networks:
    my_network:
  ```

- The Docker images themselves are identical in both approaches, but docker-compose provides a more organized way to manage their deployment and configuration.

### 3. The benefit of Docker compared to VMs

**Explanation:**
- **Resource Efficiency**: Containers share the host OS kernel and use fewer resources than VMs. They start in seconds rather than minutes and require less memory and disk space.
- **Portability**: Docker containers run consistently across different environments ("build once, run anywhere"), eliminating the "it works on my machine" problem.
- **Isolation**: Containers provide process-level isolation without the overhead of running separate OS instances.
- **Speed**: Containers start and stop much faster than VMs because they don't need to boot an entire OS.
- **Density**: You can run many more containers than VMs on the same hardware.
- **DevOps Integration**: Docker integrates well with CI/CD pipelines and modern development workflows.
- **Version Control**: Container configurations can be version-controlled as code.

| **Feature** | **Docker Containers** | **Virtual Machines** |
|-------------|----------------------|----------------------|
| Size | Megabytes | Gigabytes |
| Startup Time | Seconds | Minutes |
| OS | Shares host kernel | Complete OS copy |
| Isolation | Process-level | Hardware-level |
| Resource Usage | Low overhead | Higher overhead |
| Portability | Highly portable | Less portable |

### 4. The pertinence of the directory structure required for this project

**Explanation:**
The directory structure for the Inception project follows a logical organization that enhances maintainability, security, and clarity:

 
Inception/
├── srcs/                       # Source files directory
│   ├── docker-compose.yml      # Main Docker Compose configuration      service orchestration 
│   ├── docker-compose.override.yml  # OS-specific volume configuration
│   ├── setup_env.sh            # Script to create .env file
│   └── requirements/           # Service-specific configurations
│       ├── nginx/              # NGINX configuration files
│       ├── wordpress/          # WordPress configuration files
│       └── mariadb/            # MariaDB configuration files
├── secrets/                    # Stores secure passwords
├── Makefile                    # Project automation
├── setup.sh                    # Initial project setup script
├── cleanup_docker.sh           # Docker cleanup utilities
└── Documentation files (README.md, LEARN.md, etc.)

This structure is pertinent because:

1. **Separation of Concerns**: Each service has its own directory with its Dockerfile and configuration files, making it easy to understand and modify each component independently.

2. **Security**: Sensitive data is isolated in the `secrets` directory, separate from code and configuration, following security best practices.

3. **Maintainability**: The organization makes it easy to locate and modify specific components without affecting others.

4. **Reproducibility**: The clear structure makes it easier for others to understand and reproduce the project.

5. **Scalability**: New services can be added by creating new directories in the requirements folder, following the same pattern.

6. **Centralized Configuration**: The docker-compose.yml file serves as a central point for orchestrating all services.

7. **Build Automation**: The Makefile at the root provides standardized commands for building and managing the project.

## Docker Network

### 5. Simple explanation of docker-network

**Explanation:**
Docker networks provide isolated communication channels between containers:

- **Purpose**: Docker networks allow containers to communicate with each other while remaining isolated from the host network and other container networks.

- **Name Resolution**: Containers on the same network can refer to each other by container name or service name, which Docker automatically resolves to the appropriate IP address.

- **Types of Networks**:
  - **Bridge**: The default network type that provides internal communication between containers on the same host (used in our project).
  - **Host**: Containers share the host's network namespace (not used in our project as it's prohibited).
  - **Overlay**: For communication between containers across multiple Docker hosts (not needed for our project).
  - **None**: Containers have no network access.

- **In Our Project**: We create a custom bridge network called `inception_network` that all three containers (NGINX, WordPress, and MariaDB) connect to. This allows:
  - WordPress to connect to MariaDB using the hostname "mariadb"
  - NGINX to connect to WordPress using the hostname "wordpress"
  - Only NGINX to be exposed to the outside world on port 443
  - MariaDB to remain completely internal and inaccessible from outside

- **Security Benefits**: Using a custom network improves security by isolating our containers from other Docker networks and limiting external access to only what's necessary (HTTPS via NGINX).

## MariaDB

### 6. How to login into the database

**Explanation:**
To login to the MariaDB database:

1. **Access the MariaDB Container**:
   ```bash
   docker exec -it mariadb /bin/sh
   ```

2. **Login as Root User**:
   ```bash
   mysql -u root -p
   ```
   When prompted, enter the root password stored in the Docker secret.

3. **Login as WordPress Database User**:
   ```bash
   mysql -u ${MYSQL_USER} -p
   ```
   When prompted, enter the WordPress database user password.

4. **View Databases and Tables**:
   ```sql
   SHOW DATABASES;
   USE wordpress;
   SHOW TABLES;
   ```

5. **Security Measures**:
   - Root login is restricted to localhost only
   - Passwords are required for all users
   - Database is only accessible from within the Docker network
   - Credentials are managed through Docker secrets

## Evaluation Notes

### Important: OS Detection Removal
- For the evaluation, the OS detection feature in setup scripts should be removed since evaluation will be on Linux only
- This affects:
  - `setup.sh`: Remove the OS detection logic and keep only the Linux-specific implementation
  - `Makefile`: Simplify the DATA_PATH assignment to use Linux path only
  - Any other scripts with OS-specific conditionals
- With these changes, volume binding will use the Linux approach with bind mounts rather than named volumes for macOS

### Docker Compose Files
- For a Linux-only environment (like during evaluation), the project can be simplified to use a single docker-compose.yml file
- This single file would include all service definitions and the Linux-specific volume configurations
- Benefits of combining into one file:
  - Eliminates the need for docker-compose.override.yml
  - Simplifies setup scripts by removing code that generates the override file
  - Reduces overall project complexity
  - Makes the setup more straightforward for evaluation
- If using this approach, update the Makefile to reference only the single docker-compose.yml file

### Secret Folder Management
- The subject explicitly mentions a "secret" directory in the expected structure:
  ```
  $> ls -alR
  total XX
  drwxrwxr-x 3 wil wil 4096 avril 42 20:42 .
  drwxrwxrwt 17 wil wil 4096 avril 42 20:42 ..
  -rw-rw-r-- 1 wil wil XXXX avril 42 20:42 Makefile
  drwxrwxr-x 3 wil wil 4096 avril 42 20:42 secret
  ```
- Best approach: 
  - Keep the "secret" folder structure in the project
  - For `make clean` and `make fclean` commands, only remove the password files within the folder, not the folder itself
  - When setting up, generate passwords and store them in the secret folder
  - This maintains the required directory structure while ensuring security
