# Inception Project Learning Guide

## Table of Contents
1. [Project Overview](#project-overview)
2. [Core Components](#core-components)
3. [Technical Terms](#technical-terms)
4. [Project Structure](#project-structure)
5. [Security Features](#security-features)
6. [Practical Usage](#practical-usage)
7. [Troubleshooting](#troubleshooting)
8. [Comprehensive Evaluation Study Guide](#comprehensive-evaluation-study-guide)

## Project Overview

Inception is a Docker infrastructure project that creates a complete web hosting environment using containerization. The project demonstrates:
- Service isolation through containers *containers are a way to isolate services from each other*
- Secure web hosting practices *HTTPS is a protocol that encrypts web traffic to ensure secure communication between the client and the server*
- Database management *MariaDB is a database server that allows you to store and retrieve data*
- Container orchestration *Docker Compose is a tool for defining and running multi-container Docker applications*

## Core Components

### 1. NGINX Container
**What is NGINX?**
- A high-performance web server 
- Acts as reverse proxy *reverse proxy is a server that takes requests from clients and forwards them to another server*
- Handles web traffic efficiently *nginx is designed to handle a large number of concurrent connections efficiently*

**Role in Project:**
```yaml 
nginx:
  ports:
    - "443:443"  # HTTPS only *HTTPS is a protocol that encrypts web traffic to ensure secure communication between the client and the server*
  volumes:
    - wordpress_data:/var/www/html
```
- Manages incoming web requests *nginx is a web server that can handle incoming requests from clients*
- SSL/TLS termination *SSL/TLS is a protocol that encrypts web traffic to ensure secure communication between the client and the server*
- Routes traffic to WordPress *nginx is a web server that can handle incoming requests from clients*
- Serves static content *nginx is a web server that can serve static content to the client*

### 2. WordPress + PHP-FPM Container
**What is WordPress?**
- Content Management System (CMS) *WordPress is a content management system that allows you to create a website or blog*
- Website creation platform *WordPress is a website creation platform that allows you to create a website or blog*
- Blog and content platform 

**What is PHP-FPM?**
- PHP FastCGI Process Manager *PHP-FPM is a process manager for PHP that allows you to handle PHP processing*
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
- Runs the website *WordPress is a website creation platform that allows you to create a website or blog*
- Processes PHP code *PHP-FPM is a process manager for PHP that allows you to handle PHP processing*
- Manages content
- Communicates with database 

### 3. MariaDB Container
**What is MariaDB?**
- Open-source database server *MariaDB is an open-source database server that allows you to store and retrieve data*
- Fork of MySQL *MariaDB is a fork of MySQL*
- Stores all website data *MariaDB is a database server that allows you to store and retrieve data*

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

## Comprehensive Evaluation Study Guide

### Docker and Containerization Concepts

#### 1. What is Docker and why is it used in this project?
Docker is a platform that uses containerization technology to create, deploy, and run applications in isolated environments called containers. In the Inception project, Docker provides several critical benefits:

- **Service Isolation**: Each component (NGINX, WordPress, MariaDB) runs in its own container, preventing conflicts and enhancing security.
- **Consistent Environments**: Ensures the application runs the same way in development, testing, and production.
- **Resource Efficiency**: Containers share the host OS kernel and use fewer resources than virtual machines.
- **Reproducible Deployments**: The entire infrastructure can be defined as code and rebuilt identically.
- **Scalability**: Individual services can be scaled independently based on demand.

The project uses Docker to create a modular, maintainable, and secure web infrastructure where each service operates in isolation.

#### 2. How do containers differ from virtual machines?

| **Containers** | **Virtual Machines** |
|----------------|----------------------|
| Share the host OS kernel | Run complete OS copies with their own kernels |
| Lightweight (MB) | Heavyweight (GB) |
| Start in seconds | Start in minutes |
| Use fewer resources | Require more CPU/RAM/storage |
| OS-dependent | OS-independent |
| Isolation at process level | Isolation at hardware level |

Containers are more lightweight and efficient because they share the host OS kernel instead of running a complete OS. This makes them faster to start and use fewer resources, which is ideal for the Inception project where we need to run multiple services on a single host.

#### 3. Advantages of containerization for web infrastructure

- **Isolation**: Each service runs in its own environment, improving security and stability.
- **Consistency**: Development, testing, and production environments are identical.
- **Modularity**: Services can be updated or replaced independently.
- **Resource Efficiency**: Containers share the host OS kernel and use fewer resources.
- **Portability**: The entire stack can be deployed on any system that runs Docker.
- **Scalability**: Services can be replicated easily to handle increased load.
- **Disaster Recovery**: Containers can be quickly restarted or recreated if they fail.
- **Version Control**: Infrastructure configuration can be tracked in Git.

#### 4. Docker Compose and service orchestration

Docker Compose is a tool for defining and running multi-container Docker applications. For the Inception project, it provides:

- **Service Definition**: Declares all services, networks, and volumes in a single YAML file.
- **Dependency Management**: Specifies dependencies between services (e.g., WordPress depends on MariaDB).
- **Environment Configuration**: Manages environment variables for all containers.
- **Volume Management**: Defines persistent storage for databases and files.
- **Network Configuration**: Creates isolated networks for container communication.
- **One-Command Deployment**: Starts all services with a single command.

Example from our `docker-compose.yml`:
```yaml
version: '3.8'
services:
  nginx:
    build: ./requirements/nginx
    ports:
      - "443:443"
    # Additional configuration...
  
  wordpress:
    depends_on:
      - mariadb
    # Additional configuration...
  
  mariadb:
    # Configuration...
```

### Project Architecture

#### 5. Three-container architecture and data flow

Our architecture consists of three containers with the following data flow:

1. **Client Browser**
   - Initiates HTTPS request to your domain (e.g., username.42.fr)

2. **NGINX Container**
   - Receives all incoming HTTPS requests (port 443) *HTTPS is a protocol that encrypts web traffic to ensure secure communication between the client and the server*
   - Handles SSL/TLS termination *SSL/TLS is a protocol that encrypts web traffic to ensure secure communication between the client and the server*
   - Processes static files directly (CSS, JS, images) *static files are files that are not processed by the server, such as CSS, JS, and images*
   - Forwards PHP processing requests to WordPress *PHP-FPM is a process manager for PHP that allows you to handle PHP processing*

3. **WordPress Container**
   - Processes PHP code via PHP-FPM *PHP-FPM is a process manager for PHP that allows you to handle PHP processing*
   - Handles dynamic content generation *dynamic content is content that is generated by the server, such as a blog post or a user profile*
   - Communicates with MariaDB to retrieve/store data *MariaDB is a database server that allows you to store and retrieve data*
   - Returns processed content to NGINX *NGINX is a web server that can handle incoming requests from clients*

4. **MariaDB Container**
   - Stores all WordPress data *MariaDB is a database server that allows you to store and retrieve data*
   - Handles database queries 
   - Manages user accounts, posts, settings 
   - Provides data persistence 

This separation of concerns improves security, modularity, and maintainability.

#### 6. Component communication

- **NGINX ↔ WordPress**: Communication happens via FastCGI protocol over an internal network. NGINX passes PHP requests to WordPress on port 9000.

- **WordPress ↔ MariaDB**: WordPress connects to MariaDB using MySQL protocol over the internal network on port 3306.

- **Container Network**: All services share the same Docker network (`inception_network`), allowing containers to communicate using service names as hostnames.

Example configuration:
```nginx
# NGINX configuration for PHP processing
location ~ \.php$ {
    fastcgi_pass wordpress:9000;  # WordPress container name:port
    fastcgi_index index.php;
    include fastcgi_params;
    fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
}
```

```php
// WordPress database configuration
define('DB_HOST', 'mariadb');  // MariaDB container name
define('DB_USER', '${MYSQL_USER}');
define('DB_PASSWORD', '${MYSQL_PASSWORD}');
```

#### 7. Base image selection rationale

Alpine/Debian was chosen as the base image for several reasons:

- **Alpine Benefits**:
  - Extremely lightweight (5-10MB vs 100-200MB for full distros)
  - Security-focused design with minimal attack surface
  - Active maintenance and security updates
  - Sufficient package availability through apk

- **Debian Benefits** (if used):
  - Extremely stable and well-tested
  - Comprehensive package repository
  - Excellent compatibility with most software
  - Long-term support

- **Avoiding 'latest' tag**:
  - Using specific versions ensures reproducibility
  - Prevents unexpected changes when rebuilding
  - Improves stability by using known-good versions

#### 8. Service isolation implementation

Service isolation is achieved through several Docker features:

1. **Container Boundaries**: Each service runs in its own container with isolated processes, filesystems, and network namespaces.

2. **Network Segmentation**: Custom bridge network allows controlled communication between containers.

3. **Volume Isolation**: Each service has access only to its required volumes.

4. **Resource Limits**: Can specify CPU and memory limits for each container.

5. **User Separation**: Services run as non-root users inside containers.

6. **Controlled Access**: Only necessary ports are exposed.

Example from `docker-compose.yml`:
```yaml
services:
  nginx:
    # Only NGINX exposes a port to the host
    ports:
      - "443:443"
    # Other services are not directly accessible from outside
```

### NGINX Container

#### 9. SSL/TLS configuration in NGINX

SSL/TLS is configured in NGINX through several key settings:

1. **Certificate Configuration**:
   ```nginx
   ssl_certificate /etc/nginx/ssl/inception.crt;
   ssl_certificate_key /etc/nginx/ssl/inception.key;
   ```

2. **Protocol Selection**:
   ```nginx
   ssl_protocols TLSv1.2 TLSv1.3;  # Only secure versions
   ```

3. **Cipher Configuration**:
   ```nginx
   ssl_prefer_server_ciphers on;
   ssl_ciphers ECDHE-RSA-AES256-GCM-SHA512:DHE-RSA-AES256-GCM-SHA512:ECDHE-RSA-AES256-GCM-SHA384:DHE-RSA-AES256-GCM-SHA384;
   ```

4. **SSL Session Management**:
   ```nginx
   ssl_session_timeout 10m;
   ssl_session_cache shared:SSL:10m;
   ```

5. **HTTPS Enforcement**:
   ```nginx
   server {
       listen 443 ssl;
       # No HTTP listener defined
   }
   ```

The certificates are generated during the Docker build process and stored in the appropriate location.

#### 10. Port 443 only (no port 80)

Only port 443 (HTTPS) is exposed for several reasons:

1. **Security**: Forces all traffic to be encrypted.
2. **Project Requirements**: The subject explicitly requires HTTPS only.
3. **Modern Standards**: Current best practices encourage HTTPS-only websites.
4. **Data Protection**: Prevents accidental transmission of sensitive data over unencrypted channels.
5. **Simplicity**: No need to handle HTTP-to-HTTPS redirects.

By omitting port 80, we ensure all communication with the web server is secure from end to end.

#### 11. NGINX as a reverse proxy for WordPress

NGINX acts as a reverse proxy by:

1. **Receiving Client Requests**: Accepts all incoming HTTPS connections.
2. **Processing Static Content**: Handles static files directly (images, CSS, JS).
3. **Forwarding PHP Requests**: Sends PHP processing to WordPress container.
4. **Load Balancing**: Can distribute requests if multiple WordPress containers exist.
5. **Caching**: Can cache responses to improve performance.

Configuration example:
```nginx
# Static content handling
location ~* \.(jpg|jpeg|png|gif|ico|css|js)$ {
    expires max;
    log_not_found off;
}

# PHP processing
location ~ \.php$ {
    fastcgi_pass wordpress:9000;
    include fastcgi_params;
    fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
}
```

This separation of responsibilities improves performance and security by letting each component focus on its specialization.

#### 12. TLS versions and rationale

Only TLSv1.2 and TLSv1.3 are allowed:
```nginx
ssl_protocols TLSv1.2 TLSv1.3;
```

Reasons for this restriction:
1. **Security**: TLSv1.0 and TLSv1.1 have known vulnerabilities.
2. **Compliance**: PCI-DSS and other standards require TLSv1.2 or higher.
3. **Modern Support**: All current browsers support TLSv1.2/1.3.
4. **Performance**: TLSv1.3 offers improved speed with fewer round-trips.
5. **Future-Proofing**: Using latest protocols prevents obsolescence.

Older versions (SSLv3, TLSv1.0, TLSv1.1) are explicitly excluded due to vulnerabilities like POODLE, BEAST, and FREAK.

### WordPress & PHP-FPM

#### 13. PHP-FPM configuration

PHP-FPM is configured for optimal performance and security:

```ini
[www]
user = wordpress
group = wordpress
listen = 9000
listen.owner = wordpress
listen.group = wordpress

pm = dynamic
pm.max_children = 5
pm.start_servers = 2
pm.min_spare_servers = 1
pm.max_spare_servers = 3
pm.max_requests = 500

php_admin_value[memory_limit] = 256M
php_admin_value[upload_max_filesize] = 64M
php_admin_value[post_max_size] = 64M
php_admin_value[max_execution_time] = 300
```

Key points:
- **Non-root User**: Runs as `wordpress` user for security
- **Process Manager**: Dynamic PM optimizes resource usage
- **Connection Socket**: Listens on port 9000
- **Resource Limits**: Controls memory and execution time
- **Upload Settings**: Configures file upload capabilities

#### 14. WordPress initialization process

The WordPress installation and setup process follows these steps:

1. **Prerequisite Installation**:
   - PHP and necessary extensions
   - WP-CLI for command-line management

2. **Download WordPress**:
   ```bash
   wp core download --allow-root
   ```

3. **Configuration Generation**:
   ```bash
   wp config create --dbname=${MYSQL_DATABASE} --dbuser=${MYSQL_USER} --dbpass=${MYSQL_PASSWORD} --dbhost=mariadb --allow-root
   ```

4. **Database Setup**:
   ```bash
   wp core install --url=${DOMAIN_NAME} --title=${WP_TITLE} --admin_user=${WP_ADMIN_USER} --admin_password=${WP_ADMIN_PASSWORD} --admin_email=${WP_ADMIN_EMAIL} --allow-root
   ```

5. **User Creation**:
   ```bash
   wp user create ${WP_USER} ${WP_USER_EMAIL} --role=author --user_pass=${WP_USER_PASSWORD} --allow-root
   ```

This process uses environment variables and Docker secrets for configuration, ensuring security and repeatability.

#### 15. WordPress credential management

WordPress credentials are managed securely using:

1. **Environment Variables**: Sensitive data passed as environment variables in `docker-compose.yml`.
   ```yaml
   environment:
     WP_ADMIN_USER: ${WP_ADMIN_USER}
     WP_USER: ${WP_USER}
   ```

2. **Docker Secrets**: Passwords stored as Docker secrets.
   ```yaml
   secrets:
     - source: wp_admin_password
     - source: wp_user_password
   ```

3. **Secrets Files**: Actual credentials stored in files outside the image.
   ```
   secrets/wp_admin_password.txt
   secrets/wp_user_password.txt
   ```

4. **Runtime Access**: Credentials retrieved within the container:
   ```bash
   WP_ADMIN_PASSWORD=$(cat /run/secrets/wp_admin_password)
   ```

This approach ensures:
- Credentials never appear in the Docker image
- Passwords aren't visible in process lists
- Each service only accesses its required secrets

#### 16. wp-config.php purpose and generation

The `wp-config.php` file is WordPress's primary configuration file that defines:
- Database connection details
- Authentication keys and salts
- Debug settings
- File system access methods
- Language settings
- Cache configuration

It's generated using WP-CLI with secure settings:
```bash
wp config create \
  --dbname=${MYSQL_DATABASE} \
  --dbuser=${MYSQL_USER} \
  --dbpass=${MYSQL_PASSWORD} \
  --dbhost=mariadb \
  --allow-root
```

Additional security settings are added:
```php
define('WP_DEBUG', false);
define('FORCE_SSL_ADMIN', true);
define('AUTOMATIC_UPDATER_DISABLED', true);
```

The file is protected with limited permissions:
```bash
chmod 640 wp-config.php
```

### MariaDB Container

#### 17. MariaDB initialization and security

MariaDB is initialized with a secure configuration:

1. **Base Configuration**:
   ```cnf
   [mysqld]
   user = mysql
   bind-address = 0.0.0.0
   skip-networking = false
   port = 3306
   ```

2. **Database Creation Script**:
   ```sql
   CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
   CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
   GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
   
   -- Security measures
   ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
   DELETE FROM mysql.user WHERE User='';
   DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost');
   FLUSH PRIVILEGES;
   ```

3. **Security Hardening**:
   - No remote root access
   - Removed anonymous users
   - Limited network access
   - Non-root container user

4. **Initialization Process**:
   - Load configuration files
   - Initialize database directory
   - Create required databases and users
   - Apply security settings

#### 18. Database credential management

Database credentials are managed through multiple security layers:

1. **Environment Variables**: For non-sensitive information.
   ```yaml
   environment:
     MYSQL_DATABASE: ${MYSQL_DATABASE}
     MYSQL_USER: ${MYSQL_USER}
   ```

2. **Docker Secrets**: For passwords.
   ```yaml
   secrets:
     - source: db_root_password
     - source: db_password
   ```

3. **Initialization Script**: Uses variables to configure database.
   ```bash
   mysqld --initialize-insecure --user=mysql
   mysql -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';"
   ```

4. **Secure Storage**: Passwords stored in files with restricted access.
   ```
   secrets/db_root_password.txt
   secrets/db_password.txt
   ```

This approach ensures:
- No hardcoded credentials in images
- Proper privilege separation
- Limited credential exposure

#### 19. Database data persistence

When containers restart:

1. **Data Location**: Database files are stored in a persistent volume:
   ```yaml
   volumes:
     - ${DATA_PATH}/mariadb:/var/lib/mysql
   ```

2. **Restart Process**:
   - Container stops gracefully (SIGTERM)
   - Database performs clean shutdown
   - When restarted, MariaDB detects existing data
   - Database starts with existing tables and data
   - No initialization script runs if data exists

3. **Volume Mapping**: The host directory at `${DATA_PATH}/mariadb` maps to `/var/lib/mysql` in the container, making all database files persistent.

4. **Startup Checks**: The initialization script checks for existing data:
   ```bash
   if [ -d "/var/lib/mysql/mysql" ]; then
       # Data exists, skip initialization
   else
       # Initialize new database
   fi
   ```

This ensures all website data remains intact across container restarts.

#### 20. Database security measures

MariaDB security is implemented through multiple layers:

1. **Network Security**:
   - Database only accessible on internal Docker network
   - No direct exposure to the host or internet
   - Communication restricted to WordPress container

2. **Authentication**:
   - Strong password enforcement
   - No anonymous users
   - Remote root access disabled

3. **Authorization**:
   - Each user has minimum required privileges
   - WordPress user has access only to its database

4. **Configuration Hardening**:
   ```cnf
   [mysqld]
   symbolic-links=0
   local-infile=0
   user = mysql
   ```

5. **Container Security**:
   - Non-root user for database processes
   - Limited file system access
   - No unnecessary packages

6. **Initialization Security**:
   ```sql
   -- Remove test database
   DROP DATABASE IF EXISTS test;
   -- Remove anonymous users
   DELETE FROM mysql.user WHERE User='';
   -- Restrict root to localhost
   DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost');
   ```

### Volumes and Persistence

#### 21. Persistent data storage location

Persistent data is stored in:

1. **WordPress Data**:
   - Host: `/home/${USER}/data/wordpress`
   - Container: `/var/www/html`
   - Contents: WordPress files, uploads, themes, plugins

2. **MariaDB Data**:
   - Host: `/home/${USER}/data/mariadb`
   - Container: `/var/lib/mysql`
   - Contents: Database files, tables, indexes

The `${DATA_PATH}` variable in docker-compose.yml contains the platform-specific path (Linux or macOS).

#### 22. Volume definitions and rationale

Volumes are defined as bind mounts in `docker-compose.yml`:

```yaml
services:
  wordpress:
    volumes:
      - ${DATA_PATH}/wordpress:/var/www/html
  
  mariadb:
    volumes:
      - ${DATA_PATH}/mariadb:/var/lib/mysql
```

Rationale for each volume:
- **WordPress Volume**: 
  - Preserves uploads, themes, plugins, and core files
  - Ensures content changes persist across restarts
  - Allows backup and restore operations
  - Required for media uploads functionality

- **MariaDB Volume**:
  - Maintains database tables, indexes, and data
  - Preserves user accounts and settings
  - Ensures data integrity across restarts
  - Critical for website functionality

The bind mount approach ensures data is easily accessible on the host system.

#### 23. Effects of stopping and removing containers

If all containers are stopped and removed:

1. **Container State**: All running processes terminate.
2. **Ephemeral Data**: Any data stored only within containers (not in volumes) is lost.
3. **Container Filesystem**: All container-specific changes are deleted.
4. **Network**: The Docker network may be removed if explicitly deleted.

However, with proper volume configuration:
1. **Persistent Data**: All data in `/home/${USER}/data/wordpress` and `/home/${USER}/data/mariadb` remains intact.
2. **Environment Variables**: Values defined in `.env` remain.
3. **Secrets**: Files in the `secrets` directory remain.

When containers are recreated using the same docker-compose.yml:
1. **Data Reattachment**: Volumes reconnect to the same host directories.
2. **Service Recovery**: All services restart with existing data.
3. **Website Functionality**: The website continues with all content intact.

#### 24. Data persistence testing

Testing data persistence involves:

1. **Create Test Content**:
   - Login to WordPress admin
   - Create a test post with unique title
   - Upload sample images
   - Install a test plugin

2. **Container Restart Test**:
   ```bash
   docker compose down
   docker compose up -d
   ```

3. **Verification**:
   - Confirm WordPress site loads after restart
   - Verify test post still exists with images
   - Check plugin remains installed
   - Confirm user accounts still work

4. **Database Test**:
   ```bash
   docker exec mariadb mysql -uroot -p${MYSQL_ROOT_PASSWORD} -e "SHOW TABLES FROM wordpress;"
   ```
   This should show all WordPress tables intact.

5. **File Persistence Test**:
   ```bash
   docker exec wordpress ls -la /var/www/html/wp-content/uploads
   ```
   This should show all uploaded media files.

### Network Configuration

#### 25. Network configuration in docker-compose.yml

The network configuration is defined in `docker-compose.yml`:

```yaml
networks:
  inception_network:
    name: ${NETWORK_NAME}
    driver: bridge
```

Service network assignments:
```yaml
services:
  nginx:
    networks:
      - inception_network
  
  wordpress:
    networks:
      - inception_network
  
  mariadb:
    networks:
      - inception_network
```

This creates a dedicated bridge network for all three containers, allowing them to communicate with each other while remaining isolated from the host network and other Docker networks.

#### 26. Network isolation importance

Network isolation is crucial for:

1. **Security**: Containers can only communicate with containers on the same network, preventing unauthorized access.

2. **Name Resolution**: Services can use container names as hostnames (e.g., WordPress connects to `mariadb`).

3. **Port Conflict Prevention**: Internal ports don't conflict with host ports.

4. **Attack Surface Reduction**: Only NGINX is exposed to the host, reducing the attack vectors.

5. **Controlled Access**: MariaDB is never directly accessible from outside the Docker network.

6. **Clear Architecture**: Network dependencies are explicitly defined.

7. **Simplified Configuration**: No need for explicit IP addresses in configuration files.

#### 27. Container discovery on the network

Containers find each other through:

1. **Docker DNS**: Automatic name resolution on the custom network.
   - `mariadb` hostname resolves to the MariaDB container's IP
   - `wordpress` hostname resolves to the WordPress container's IP
   - `nginx` hostname resolves to the NGINX container's IP

2. **Service Names**: Container names are used as hostnames in configuration.
   ```php
   // In WordPress config
   define('DB_HOST', 'mariadb');
   ```
   
   ```nginx
   # In NGINX config
   fastcgi_pass wordpress:9000;
   ```

3. **Network Isolation**: All containers are on the `inception_network`, enabling communication.

4. **Dependency Order**: `depends_on` in docker-compose.yml ensures services start in the correct order:
   ```yaml
   wordpress:
     depends_on:
       - mariadb
   
   nginx:
     depends_on:
       - wordpress
   ```

This automatic discovery eliminates the need for hardcoded IP addresses.

### Security Implementation

#### 28. Password and sensitive data management

Sensitive data is managed using multiple methods:

1. **Environment Variables**:
   - Non-sensitive data in docker-compose.yml
   - Values sourced from .env file
   ```yaml
   environment:
     MYSQL_DATABASE: ${MYSQL_DATABASE}
     WP_ADMIN_USER: ${WP_ADMIN_USER}
   ```

2. **Docker Secrets**:
   - Passwords and credentials
   - Mounted as files in containers
   ```yaml
   secrets:
     db_password:
       file: ../secrets/db_password.txt
   ```

3. **Secrets Directory**:
   - External to Docker images
   - Contains credential files
   - Limited access permissions
   ```bash
   chmod 600 secrets/*.txt
   ```

4. **Runtime Access**:
   - Containers read secrets at runtime
   - No credentials in environment variables
   ```bash
   WP_ADMIN_PASSWORD=$(cat /run/secrets/wp_admin_password)
   ```

This approach ensures credentials are never embedded in images or exposed in process listings.

#### 29. Secrets management approach

Our secrets management approach involves:

1. **Secrets Generation**:
   - Random passwords generated with `openssl rand`
   - Stored in text files in the secrets directory
   ```bash
   openssl rand -base64 32 | tr -d '/+=' | cut -c1-16 > secrets/db_password.txt
   ```

2. **Secret Definition**:
   - Docker Compose secrets section
   ```yaml
   secrets:
     db_root_password:
       file: ../secrets/db_root_password.txt
     db_password:
       file: ../secrets/db_password.txt
     wp_admin_password:
       file: ../secrets/wp_admin_password.txt
     wp_user_password:
       file: ../secrets/wp_user_password.txt
   ```

3. **Secret Assignment**:
   - Each service only receives required secrets
   ```yaml
   wordpress:
     secrets:
       - db_password
       - wp_admin_password
       - wp_user_password
   ```

4. **Secret Access**:
   - Mounted at `/run/secrets/` in containers
   - Read by initialization scripts
   ```bash
   MYSQL_PASSWORD=$(cat /run/secrets/db_password)
   ```

5. **Credential Summary**:
   - User-friendly credentials.txt for reference
   ```
   secrets/credentials.txt
   ```

This approach provides strong security while maintaining usability.

#### 30. Why credentials shouldn't be in Dockerfiles

Storing credentials in Dockerfiles is problematic because:

1. **Image History**: Every layer in a Docker image is preserved in history, including build args:
   ```bash
   docker history image_name
   ```

2. **Version Control**: Dockerfiles are typically stored in Git, exposing credentials.

3. **Reproducibility Issues**: Hardcoded credentials make images less portable.

4. **Docker Hub Risks**: Public images with credentials are security vulnerabilities.

5. **Credential Rotation**: Changing passwords requires rebuilding images.

6. **Principle of Least Privilege**: Separating code from credentials is a security best practice.

7. **Audit Challenges**: Harder to track who has access to credentials.

Instead, the project uses Docker secrets and environment variables, which are provided at runtime and not baked into images.

#### 31. SSL implementation security benefits

Our SSL implementation enhances security through:

1. **Encryption in Transit**: All data between client and server is encrypted.

2. **Modern TLS Only**: 
   ```nginx
   ssl_protocols TLSv1.2 TLSv1.3;
   ```
   Only secure, modern TLS versions are allowed.

3. **Strong Cipher Suites**:
   ```nginx
   ssl_ciphers ECDHE-RSA-AES256-GCM-SHA512:DHE-RSA-AES256-GCM-SHA512:ECDHE-RSA-AES256-GCM-SHA384:DHE-RSA-AES256-GCM-SHA384;
   ```
   Only high-strength ciphers are permitted.

4. **Perfect Forward Secrecy**:
   ECDHE and DHE cipher suites ensure that compromised keys can't decrypt past traffic.

5. **HTTPS Only**:
   No HTTP listener exists, forcing all connections to use HTTPS.

6. **HSTS Implementation**:
   ```nginx
   add_header Strict-Transport-Security "max-age=31536000; includeSubDomains" always;
   ```
   Tells browsers to only use HTTPS.

7. **Secure Cookies**:
   WordPress is configured to use secure cookies:
   ```php
   define('FORCE_SSL_ADMIN', true);
   ```

These measures protect against eavesdropping, man-in-the-middle attacks, and session hijacking.

### Project Requirements

#### 32. Meeting subject requirements

The project meets requirements through:

1. **Three-Container Structure**:
   - NGINX, WordPress+PHP-FPM, and MariaDB in separate containers

2. **Volume Configuration**:
   - WordPress data in `/home/${USER}/data/wordpress`
   - MariaDB data in `/home/${USER}/data/mariadb`

3. **Docker Network**:
   - Custom bridge network for container communication
   - No use of `host` network or `--link` flags

4. **NGINX as Entry Point**:
   - Only NGINX container exposes ports
   - HTTPS only on port 443
   - TLSv1.2/TLSv1.3 only

5. **WordPress Setup**:
   - WordPress with PHP-FPM configuration
   - Admin user without forbidden names
   - Second user with limited permissions

6. **MariaDB Configuration**:
   - Database properly initialized
   - Secure password management
   - Data persistence

7. **Dockerfile Requirements**:
   - Uses Alpine or Debian
   - No `latest` tags
   - No pre-built images except base OS

8. **Security Requirements**:
   - No passwords in Dockerfiles
   - Docker secrets implementation
   - Environment variables usage

Each requirement is explicitly addressed in the project implementation.

#### 33. Non-root user implementation

Non-root users are implemented in each container:

1. **NGINX Container**:
   ```Dockerfile
   # Create nginx user and group
   RUN adduser -D -H -s /sbin/nologin nginx
   # Configure NGINX to run as nginx user
   RUN sed -i 's/user nginx;/user nginx;/' /etc/nginx/nginx.conf
   # Switch to nginx user
   USER nginx
   ```

2. **WordPress Container**:
   ```Dockerfile
   # Create wordpress user
   RUN adduser -D -H -s /sbin/nologin wordpress
   # Set proper ownership
   RUN chown -R wordpress:wordpress /var/www/html
   # Switch to wordpress user
   USER wordpress
   ```

3. **MariaDB Container**:
   ```Dockerfile
   # MariaDB runs as mysql user by default
   RUN chown -R mysql:mysql /var/lib/mysql
   USER mysql
   ```

Benefits of non-root users:
- Reduces damage potential if container is compromised
- Follows principle of least privilege
- Improves container isolation
- Complies with security best practices

#### 34. Project testing methodology

Testing the project involves:

1. **Build Verification**:
   ```bash
   make
   ```
   Verifies all containers build successfully.

2. **Container Health Check**:
   ```bash
   docker ps
   ```
   Confirms all containers are running.

3. **Network Verification**:
   ```bash
   docker network inspect inception_network
   ```
   Checks network configuration.

4. **Volume Verification**:
   ```bash
   ls -la /home/${USER}/data/wordpress
   ls -la /home/${USER}/data/mariadb
   ```
   Confirms volume mounting.

5. **HTTPS Verification**:
   ```bash
   curl -k -I https://${DOMAIN_NAME}
   ```
   Verifies SSL configuration.

6. **WordPress Functionality Testing**:
   - Access site at https://${DOMAIN_NAME}
   - Login with admin credentials
   - Create test post and upload media
   - Create and test second user

7. **Persistence Testing**:
   ```bash
   make down
   make
   ```
   Verify all data remains after restart.

8. **Log Analysis**:
   ```bash
   docker logs nginx
   docker logs wordpress
   docker logs mariadb
   ```
   Check for errors or issues.

The `verify_inception.sh` script automates many of these tests.

#### 35. Restart policies and rationale

Restart policies are implemented in `docker-compose.yml`:

```yaml
services:
  nginx:
    restart: ${RESTART_POLICY}  # Set to unless-stopped
  
  wordpress:
    restart: ${RESTART_POLICY}
  
  mariadb:
    restart: ${RESTART_POLICY}
```

Where `RESTART_POLICY` is defined in `.env` as `unless-stopped`.

The options and rationale:

1. **`no`**: Never restart (unsuitable for production).

2. **`always`**: Always restart, even after manual stop (can cause issues during maintenance).

3. **`on-failure`**: Restart only on non-zero exit code (misses some crash scenarios).

4. **`unless-stopped`**: Restart unless explicitly stopped by user (best option).

`unless-stopped` is chosen because:
- Automatically recovers from crashes
- Survives Docker daemon restarts
- Resumes after host reboots
- Respects manual intervention
- Provides high availability
- Allows for intentional maintenance

This policy ensures maximum uptime while still allowing controlled shutdowns when needed. 