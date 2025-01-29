# Inception Project Learning Guide

## Table of Contents
1. [Project Overview](#project-overview)
2. [Core Components](#core-components)
3. [Technical Terms](#technical-terms)
4. [Project Structure](#project-structure)
5. [Security Features](#security-features)
6. [Practical Usage](#practical-usage)
7. [Troubleshooting](#troubleshooting)

## Project Overview

Inception is a Docker infrastructure project that creates a complete web hosting environment using containerization. The project demonstrates:
- Service isolation through containers
- Secure web hosting practices
- Database management
- Container orchestration

## Core Components

### 1. NGINX Container
**What is NGINX?**
- A high-performance web server
- Acts as reverse proxy
- Handles web traffic efficiently

**Role in Project:**
```yaml
nginx:
  ports:
    - "443:443"  # HTTPS only
  volumes:
    - wordpress_data:/var/www/html
```
- Manages incoming web requests
- SSL/TLS termination
- Routes traffic to WordPress
- Serves static content

### 2. WordPress + PHP-FPM Container
**What is WordPress?**
- Content Management System (CMS)
- Website creation platform
- Blog and content platform

**What is PHP-FPM?**
- PHP FastCGI Process Manager
- Handles PHP processing
- More efficient than traditional PHP

**Role in Project:**
```yaml
wordpress:
  volumes:
    - wordpress_data:/var/www/html
  depends_on:
    - mariadb
```
- Runs the website
- Processes PHP code
- Manages content
- Communicates with database

### 3. MariaDB Container
**What is MariaDB?**
- Open-source database server
- Fork of MySQL
- Stores all website data

**Role in Project:**
```yaml
mariadb:
  volumes:
    - mariadb_data:/var/lib/mysql
  secrets:
    - db_root_password
    - db_password
```
- Stores website content
- Manages user data
- Maintains website settings

## Technical Terms

### Docker Concepts
1. **Container**
   - Isolated environment
   - Runs single service
   - Shares host OS kernel
   - Lightweight virtualization

2. **Volume**
   - Persistent data storage
   - Survives container restarts
   - Shared storage between containers
   ```yaml
   volumes:
     wordpress_data:
       driver: local
       device: /home/${USER}/data/wordpress
   ```

3. **Network**
   - Container communication
   - Isolated network space
   - Secure internal routing
   ```yaml
   networks:
     inception_network:
       driver: bridge
   ```

### Web Security

1. **SSL/TLS**
   - Secure Socket Layer
   - Transport Layer Security
   - Encrypts web traffic
   ```nginx
   ssl_protocols TLSv1.2 TLSv1.3;
   ssl_prefer_server_ciphers on;
   ```

2. **HTTPS**
   - HTTP over SSL/TLS
   - Secure web communication
   - Required for modern web

3. **Secrets Management**
   - Secure password storage
   - Environment variables
   - Docker secrets feature

## Project Structure

```plaintext
Inception/
├── Makefile                  # Build automation
├── srcs/
│   ├── docker-compose.yml    # Service orchestration
│   ├── .env                  # Environment variables
│   └── requirements/         # Service configs
│       ├── nginx/           
│       ├── wordpress/
│       └── mariadb/
└── secrets/                  # Sensitive data
```

## Security Features

### 1. HTTPS Only
```nginx
server {
    listen 443 ssl;
    ssl_protocols TLSv1.2 TLSv1.3;
}
```
- No HTTP allowed
- Modern TLS versions only
- Secure communication

### 2. Docker Secrets
```yaml
secrets:
  db_password:
    file: ../secrets/db_password.txt
```
- Secure credential storage
- No plaintext passwords
- Proper secret management

### 3. Network Isolation
```yaml
networks:
  inception_network:
    driver: bridge
```
- Internal container network
- No direct external access
- Controlled communication

## Practical Usage

### Basic Commands
```bash
# Start project
make

# Stop project
make down

# Rebuild everything
make re

# View logs
docker logs nginx
docker logs wordpress
docker logs mariadb
```

### Access Points
1. Website: https://login.42.fr
2. Admin: https://login.42.fr/wp-admin
3. Database: Only through container

### Volume Management
```bash
# View volumes
docker volume ls

# Inspect volume
docker volume inspect wordpress_data

# Backup data
cp -r /home/${USER}/data/wordpress ./backup
```

## Troubleshooting

### Common Issues

1. **Container Won't Start**
   ```bash
   # Check logs
   docker logs container_name
   
   # Check status
   docker ps -a
   ```

2. **Cannot Access Website**
   - Verify NGINX running
   - Check SSL certificate
   - Confirm domain in hosts file

3. **Database Connection Failed**
   - Check MariaDB status
   - Verify credentials
   - Check network connectivity

### Debug Commands
```bash
# Container status
docker ps

# Network check
docker network inspect inception_network

# Volume check
docker volume ls

# Process check
docker top container_name
```

### Best Practices
1. Always use version control
2. Keep secrets secure
3. Regular backups
4. Monitor logs
5. Use proper restart policies

## Learning Resources

1. **Docker Documentation**
   - [Docker Get Started](https://docs.docker.com/get-started/)
   - [Docker Compose](https://docs.docker.com/compose/)

2. **NGINX Learning**
   - [NGINX Docs](https://nginx.org/en/docs/)
   - [NGINX Config Guide](https://nginx.org/en/docs/beginners_guide.html)

3. **WordPress Development**
   - [WordPress Docs](https://wordpress.org/documentation/)
   - [WP CLI Handbook](https://make.wordpress.org/cli/handbook/)

4. **MariaDB Reference**
   - [MariaDB Docs](https://mariadb.org/documentation/)
   - [Database Admin](https://mariadb.com/kb/en/library/documentation/) 