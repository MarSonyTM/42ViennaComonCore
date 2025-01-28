# Inception

This project sets up a small infrastructure composed of different services using Docker containers. The infrastructure includes NGINX, WordPress with PHP-FPM, and MariaDB, each running in its own container.

## Project Structure
```
Inception/
├── Makefile
├── README.md
├── secrets/
│   ├── credentials.txt
│   ├── db_password.txt
│   └── db_root_password.txt
└── srcs/
    ├── .env
    ├── docker-compose.yml
    └── requirements/
        ├── mariadb/
        │   ├── conf/
        │   ├── tools/
        │   └── Dockerfile
        ├── nginx/
        │   ├── conf/
        │   ├── tools/
        │   └── Dockerfile
        └── wordpress/
            ├── conf/
            ├── tools/
            └── Dockerfile
```

## Available Commands

### Basic Usage
- `make all`: Set up directories and start containers (default command)
- `make up`: Start all containers
- `make down`: Stop all containers
- `make re`: Rebuild and restart all services

### Cleanup Commands
- `make clean`: Stop containers and remove all Docker resources (containers, networks, volumes)
- `make fclean`: Perform full cleanup, including removing all data directories

### Utility Commands
- `make status`: Display status of containers, volumes, and networks
- `make logs`: Show logs from all containers
- `make shell service=<name>`: Enter a shell in a specific container
  - Example: `make shell service=wordpress`

### Directory Structure
All persistent data is stored in `/home/$USER/data/`:
- `/home/$USER/data/wordpress`: WordPress files
- `/home/$USER/data/mariadb`: MariaDB database files

## Services

### NGINX
- Acts as the only entry point to the infrastructure
- Handles SSL/TLS termination
- Listens on port 443 only
- Uses TLSv1.2 or TLSv1.3

### WordPress + PHP-FPM
- WordPress installation with PHP-FPM
- Configured without NGINX
- Connected to MariaDB

### MariaDB
- Database service for WordPress
- Persistent data storage
- Secure credential management

## Important Notes
1. No passwords in Dockerfiles
2. No infinite loops in containers
3. No latest tags
4. No ready-made Docker images (except base Alpine/Debian)
5. No network:host or --link usage
6. All services in dedicated containers
7. NGINX as only entrypoint
8. Containers must restart on crash
9. WordPress admin username restrictions
10. Environment variables mandatory 