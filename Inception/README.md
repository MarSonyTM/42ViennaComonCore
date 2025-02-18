# Inception

A Docker infrastructure project that sets up a complete WordPress development environment using multiple containers. The project demonstrates containerization best practices, secure configuration, and proper service isolation.

## Overview

This project creates a small infrastructure composed of different services, each running in its own Docker container:

- NGINX with SSL/TLS
- WordPress with PHP-FPM
- MariaDB database

## Key Features

- **Security First**: TLSv1.2/TLSv1.3 only, secure secrets management
- **Service Isolation**: Each service runs in its dedicated container
- **Data Persistence**: Volumes for both WordPress and database data
- **High Availability**: Automatic container restart on failure
- **Modern Configuration**: Using latest stable versions and best practices

## Technical Specifications

### NGINX Container
- Based on Alpine 3.17
- SSL/TLS termination (TLSv1.2/1.3)
- Reverse proxy to WordPress
- Security headers configured
- Port 443 only

### WordPress Container
- Based on Alpine 3.17
- PHP-FPM 8.1 configured
- WP-CLI for management
- Custom user configuration
- Volume mounted for persistence

### MariaDB Container
- Based on Alpine 3.17
- Secure initialization
- Custom user configuration
- Volume mounted for persistence
- Health checks enabled

## Prerequisites

- Docker Engine
- Docker Compose
- Make utility
- 1GB+ free disk space
- Port 443 available

## Installation

### System Requirements
- Ubuntu 24.04 LTS or similar
- 2GB RAM minimum
- 10GB free disk space
- Port 443 available
- sudo privileges

### Prerequisites Installation
```bash
# Update system packages
sudo apt update && sudo apt upgrade -y

# Install required packages
sudo apt install make docker.io docker-compose-v2 curl -y

# Add user to docker group
sudo usermod -aG docker $USER
# Log out and log back in for group changes to take effect
```

### Project Setup
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd inception
   ```

2. Start Docker service:
   ```bash
   # Ensure Docker service is running
   sudo systemctl start docker
   # Verify Docker is running
   docker info
   ```

3. Configure environment:
   ```bash
   # Create data directories
   make setup

   # Verify environment variables in srcs/.env
   # Update domain name and credentials if needed
   ```

4. Configure local domain:
   ```bash
   # Add domain to hosts file
   echo "127.0.0.1 mafurnic.42.fr" | sudo tee -a /etc/hosts
   ```

5. Start services:
   ```bash
   make up
   # Wait for all containers to be healthy
   make status
   ```

6. Verify installation:
   ```bash
   # Check all services
   make status

   # View logs if needed
   make logs

   # Access WordPress at https://mafurnic.42.fr
   ```

### Post-Installation
- Access WordPress admin: https://mafurnic.42.fr/wp-admin
- Default users created:
  - Admin: supervisor (credentials in secrets/credentials.txt)
  - Author: mafurnic (credentials in secrets/credentials.txt)
- MariaDB access:
  - Database: wordpress
  - User: wp_user (password in secrets/db_password.txt)
  - Root password in secrets/db_root_password.txt

### Common Setup Issues
1. **Port 443 in use**
   ```bash
   # Check what's using port 443
   sudo lsof -i :443
   # Stop the service if needed
   sudo systemctl stop apache2  # Example for Apache
   ```

2. **Permission Issues**
   ```bash
   # Fix data directory permissions
   sudo chown -R $USER:$USER /home/$USER/data
   ```

3. **Docker Issues**
   ```bash
   # Restart Docker service
   sudo systemctl restart docker
   # Verify Docker is running
   docker info
   ```

## Configuration

### Environment Variables
All sensitive configuration is managed through environment variables in `.env`:
- Domain configuration
- Database credentials
- WordPress settings
- Volume paths

### Secrets Management
Sensitive data is stored in the `secrets/` directory:
- Database passwords
- WordPress credentials
- SSL certificates

### Volume Configuration
Data persistence is managed through Docker volumes:
- WordPress files: `/home/$USER/data/wordpress`
- MariaDB data: `/home/$USER/data/mariadb`

## Configuration Details

### Environment Variables (.env)
```env
# Domain Configuration
DOMAIN_NAME=your-login.42.fr    # Your domain name

# MariaDB Configuration
MYSQL_DATABASE=wordpress        # Database name
MYSQL_USER=wp_user             # Database user
MYSQL_PASSWORD_FILE=...        # Path to password file
MYSQL_ROOT_PASSWORD_FILE=...   # Path to root password file

# WordPress Configuration
WP_TITLE=Inception             # Site title
WP_ADMIN_USER=supervisor       # Admin username (no 'admin' allowed)
WP_ADMIN_EMAIL=...            # Admin email
```

### Service Configurations

#### NGINX
- Configuration: `srcs/requirements/nginx/conf/`
- SSL certificates: Auto-generated in container
- Key features:
  ```nginx
  # SSL Configuration
  ssl_protocols TLSv1.2 TLSv1.3;
  ssl_prefer_server_ciphers on;
  
  # Security Headers
  add_header X-Frame-Options "SAMEORIGIN";
  add_header X-XSS-Protection "1; mode=block";
  ```

#### PHP-FPM
- Configuration: `srcs/requirements/wordpress/conf/www.conf`
- Key settings:
  ```ini
  pm = dynamic
  pm.max_children = 5
  pm.start_servers = 2
  upload_max_filesize = 64M
  ```

#### MariaDB
- Configuration: `srcs/requirements/mariadb/conf/my.cnf`
- Key settings:
  ```ini
  character-set-server = utf8mb4
  collation-server = utf8mb4_general_ci
  max_allowed_packet = 64M
  ```

### Volume Management

#### WordPress Volume
- Path: `/home/$USER/data/wordpress`
- Contains:
  - WordPress core files
  - Themes and plugins
  - Uploaded media
- Permissions: `nobody:nobody`

#### MariaDB Volume
- Path: `/home/$USER/data/mariadb`
- Contains:
  - Database files
  - MySQL socket
  - Error logs
- Permissions: `mysql:mysql`

### Network Configuration
- Type: Bridge network
- Name: inception_network
- Internal communication:
  - WordPress → MariaDB: Port 3306
  - NGINX → WordPress: Port 9000
  - External → NGINX: Port 443

### Security Measures
1. **SSL/TLS**
   - Self-signed certificate
   - TLSv1.2/1.3 only
   - Strong cipher suite

2. **Database**
   - No root access from outside
   - Custom user with limited privileges
   - Secure password storage

3. **WordPress**
   - Custom admin username
   - No default plugins
   - Regular updates enabled

4. **Container Security**
   - No privileged containers
   - Minimal base images
   - Limited exposed ports

### Performance Tuning

1. **NGINX**
   ```nginx
   # Performance settings
   worker_processes auto;
   keepalive_timeout 65;
   gzip on;
   ```

2. **PHP-FPM**
   ```ini
   # Resource management
   pm.max_children = 5
   pm.max_requests = 500
   ```

3. **MariaDB**
   ```ini
   # Buffer settings
   max_allowed_packet = 64M
   ```

## Available Commands

### Basic Usage
- `make all`: Set up and start everything (default)
- `make up`: Start all containers
- `make down`: Stop all containers
- `make re`: Rebuild and restart services

### Cleanup Commands
- `make clean`: Remove Docker resources
- `make fclean`: Complete cleanup including data

### Utility Commands
- `make status`: Show container status
- `make logs`: View container logs
- `make shell service=<name>`: Enter container shell

## Security Features

1. **SSL/TLS Security**
   - TLSv1.2/1.3 protocols only
   - Strong cipher suite configuration
   - Self-signed certificates (customizable)

2. **Network Security**
   - Isolated Docker network
   - No host network exposure
   - Internal service communication only

3. **Access Control**
   - Custom WordPress admin user
   - Secure database user configuration
   - No default credentials

4. **Data Protection**
   - Secrets management
   - Volume persistence
   - Secure file permissions

## Service Architecture

```
Client Request
     ↓
 [Port 443]
     ↓
[NGINX SSL]
     ↓
[WordPress + PHP-FPM]
     ↓
 [MariaDB]
```

## Troubleshooting

### Common Issues

1. **Port Conflicts**
   - Ensure port 443 is available
   - Check for other web servers

2. **Volume Permissions**
   - Verify directory ownership
   - Check mount points

3. **Database Connection**
   - Verify network connectivity
   - Check credentials
   - Ensure MariaDB is healthy

### Debug Commands
- `make logs`: View service logs
- `make status`: Check container status
- `docker network inspect inception_network`: Check network

## Best Practices Implemented

1. **Container Design**
   - Single responsibility principle
   - No latest tags
   - Proper base images
   - Clean shutdown handling

2. **Security**
   - No passwords in Dockerfiles
   - Environment variable usage
   - Proper secret management
   - Minimal container access

3. **Performance**
   - Optimized configurations
   - Resource management
   - Proper caching setup

## Maintenance

### Backup
- WordPress files in `/home/$USER/data/wordpress`
- Database files in `/home/$USER/data/mariadb`
- Configuration in `srcs/` directory

### Updates
1. Modify version numbers in Dockerfiles
2. Rebuild containers: `make re`
3. Verify functionality

## Contributing

1. Fork the repository
2. Create feature branch
3. Commit changes
4. Push to branch
5. Create Pull Request

## License

This project is part of the 42 School curriculum. 