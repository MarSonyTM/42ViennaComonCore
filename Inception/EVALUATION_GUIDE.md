# Inception Project Evaluation Guide

## 1. Project Overview
This project involves setting up a small infrastructure composed of different services using Docker containers. The main components are:

### Mandatory Services:
- **NGINX**: Web server with TLS/SSL
- **WordPress + php-fpm**: Content Management System
- **MariaDB**: Database server

### Key Requirements:
- Each service runs in its own container
- Containers are built using Alpine Linux
- Each service has its own Dockerfile
- Containers restart automatically if they crash

## 2. Infrastructure Setup

### Docker Compose Configuration
- Located in: `srcs/docker-compose.yml`
- Defines all services, networks, and volumes
- Uses version '3.8'

### Directory Structure:
```
srcs/
├── docker-compose.yml
├── .env (environment variables)
├── requirements/
│   ├── nginx/
│   ├── wordpress/
│   └── mariadb/
└── volumes/
    ├── wordpress/
    └── mariadb/
```

## 3. Service Details

### NGINX Container
- **Port**: 443 only (HTTPS)
- **SSL/TLS**: TLSv1.2 or TLSv1.3 only
- **Configuration**: Located in `srcs/requirements/nginx/conf/`
- **Key Points**:
  - Acts as reverse proxy for WordPress
  - SSL certificate properly configured
  - No HTTP (port 80) access

### WordPress Container
- **Setup**: Using php-fpm (no Apache)
- **Configuration**: Located in `srcs/requirements/wordpress/`
- **Key Points**:
  - Connected to MariaDB
  - wp-config.php properly configured
  - PHP-FPM running on port 9000

### MariaDB Container
- **Purpose**: Database for WordPress
- **Configuration**: Located in `srcs/requirements/mariadb/`
- **Key Points**:
  - Data persistence through volumes
  - Secure password configuration
  - No root access from outside

## 4. Volume Configuration

### WordPress Volume
- **Path**: `/var/www/html`
- **Purpose**: Stores WordPress files
- **Persistence**: Data remains after container restart

### MariaDB Volume
- **Path**: `/var/lib/mysql`
- **Purpose**: Stores database files
- **Persistence**: Data remains after container restart

## 5. Network Configuration
- Custom network named `inception_network`
- Type: bridge
- Containers can communicate using service names
- Only necessary ports exposed

## 6. Security Aspects
- No passwords in Dockerfiles
- Using environment variables in `.env` file
- SSL/TLS properly configured
- No root user in containers
- Secure database access

## 7. Testing Checklist

### Basic Functionality
1. Check all containers are running:
```bash
docker ps
```
Expected: All containers should be "Up" and "healthy"

2. Check HTTPS access:
```bash
curl -k https://localhost:443
```
Expected: WordPress page should load

### Service Tests
1. **NGINX**:
   - Only accessible via HTTPS
   - SSL certificate working
   - Proper reverse proxy to WordPress

2. **WordPress**:
   - Admin panel accessible
   - Can create posts/pages
   - PHP-FPM working correctly

3. **MariaDB**:
   - WordPress can connect
   - Data persists after restart
   - Secure access configuration

### Volume Tests
1. Check volumes are mounted:
```bash
docker volume ls
```
Expected: wordpress_data and mariadb_data volumes present

2. Data persistence:
   - Create a WordPress post
   - Restart containers
   - Post should still exist

## 8. Common Issues & Solutions

### Container Issues
- **Container not starting**: Check logs with `docker logs [container_name]`
- **Health check failing**: Verify service configurations
- **Network issues**: Ensure service names resolve correctly

### WordPress Issues
- **Database connection error**: Check MariaDB credentials
- **PHP-FPM issues**: Verify www.conf configuration 