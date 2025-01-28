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

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd inception
   ```

2. Create necessary directories:
   ```bash
   make setup
   ```

3. Start the services:
   ```bash
   make up
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