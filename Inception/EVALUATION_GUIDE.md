# Inception Project Evaluation Guide

## 1. Project Overview
This project implements a complete web hosting infrastructure using Docker containerization. The goal is to create a modular, secure, and maintainable system where each service runs in isolation.

### Understanding Docker's Role
Docker allows us to create isolated environments (containers) for each service. Think of containers as lightweight virtual machines that share the host's kernel but run independently. This isolation ensures:
- Security: If one service is compromised, others remain safe
- Resource management: Each container has its own resource limits
- Easy deployment: The entire stack can be launched with one command
- Consistency: The same setup works across different environments

### Mandatory Services Explained:

#### NGINX (Web Server)
- Acts as the front door to your application
- Handles all incoming HTTPS traffic
- Provides SSL/TLS encryption for secure communication
- Reverse proxies requests to WordPress
- Why NGINX? It's lightweight, fast, and excellent at handling concurrent connections

#### WordPress + php-fpm
- WordPress: Content Management System for website creation
- PHP-FPM: PHP FastCGI Process Manager
  - Handles PHP processing separately from web server
  - More efficient than traditional PHP modules
  - Better resource management and performance

#### MariaDB
- Fork of MySQL database
- Stores all WordPress data:
  - Posts, pages, users
  - Site configuration
  - Plugin data
- Provides data persistence and reliability

## 2. Infrastructure Deep Dive

### Docker Compose Configuration Explained
The `docker-compose.yml` file orchestrates your entire infrastructure:
```yaml
version: '3.8'  # Latest stable version with all features we need

services:
  nginx:
    build: ./requirements/nginx
    ports:
      - "443:443"  # Only HTTPS port exposed
    volumes:
      - wordpress_data:/var/www/html
    networks:
      - inception_network
    # ... more configuration

  wordpress:
    build: ./requirements/wordpress
    volumes:
      - wordpress_data:/var/www/html
    depends_on:
      - mariadb
    # ... more configuration

  mariadb:
    build: ./requirements/mariadb
    volumes:
      - mariadb_data:/var/lib/mysql
    # ... more configuration
```

### Directory Structure Explained
```
srcs/
├── docker-compose.yml   # Main orchestration file
├── .env                 # Environment variables (passwords, configs)
├── requirements/        # Service-specific configurations
│   ├── nginx/          # NGINX web server files
│   │   ├── Dockerfile  # Container build instructions
│   │   └── conf/       # NGINX configuration
│   ├── wordpress/      # WordPress files
│   │   ├── Dockerfile
│   │   └── tools/      # Setup scripts
│   └── mariadb/        # Database files
│       ├── Dockerfile
│       └── conf/       # MariaDB configuration
└── volumes/            # Persistent data storage
    ├── wordpress/      # WordPress files
    └── mariadb/        # Database files
```

## 3. Detailed Service Implementation

### NGINX Container Implementation
```nginx
# Key NGINX Configuration Elements
server {
    listen 443 ssl;  # Only HTTPS
    ssl_protocols TLSv1.2 TLSv1.3;  # Modern SSL only
    
    # SSL Configuration
    ssl_certificate /etc/nginx/ssl/inception.crt;
    ssl_certificate_key /etc/nginx/ssl/inception.key;
    
    # WordPress Proxy Settings
    location / {
        proxy_pass http://wordpress:9000;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }
}
```

Key Implementation Points:
1. SSL/TLS Setup:
   - Self-signed certificates generated during build
   - Modern protocols only (TLSv1.2/1.3)
   - Secure cipher configuration

2. Reverse Proxy:
   - Forwards requests to WordPress container
   - Handles all static file serving
   - Manages PHP-FPM communication

### WordPress Container Implementation
Key Components:
1. PHP-FPM Configuration:
```ini
[www]
user = wordpress
group = wordpress
listen = 9000
pm = dynamic
pm.max_children = 5
pm.start_servers = 2
pm.min_spare_servers = 1
pm.max_spare_servers = 3
```

2. WordPress Setup:
   - wp-config.php generation
   - Database connection configuration
   - WP-CLI for management
   - Custom PHP optimizations

3. Security Measures:
   - Non-root user execution
   - File permissions hardening
   - PHP security settings

### MariaDB Container Implementation
Key Setup Elements:
1. Database Initialization:
```sql
CREATE DATABASE wordpress;
CREATE USER 'wp_user'@'%' IDENTIFIED BY '${DB_PASSWORD}';
GRANT ALL PRIVILEGES ON wordpress.* TO 'wp_user'@'%';
FLUSH PRIVILEGES;
```

2. Security Configuration:
   - Remote root access disabled
   - Password policies enforced
   - Network access restrictions

## 4. Volume Management Explained

### WordPress Volume Details
```yaml
volumes:
  wordpress_data:
    driver: local
    driver_opts:
      type: none
      device: /home/wordpress/data
      o: bind
```
- Persists through container restarts
- Stores themes, plugins, uploads
- Maintains WordPress core files

### MariaDB Volume Implementation
```yaml
volumes:
  mariadb_data:
    driver: local
    driver_opts:
      type: none
      device: /home/mariadb/data
      o: bind
```
- Stores database files
- Maintains data integrity
- Survives container recreation

## 5. Network Architecture

### Network Implementation
```yaml
networks:
  inception_network:
    driver: bridge
    ipam:
      config:
        - subnet: 172.20.0.0/16
```

Communication Flow:
1. External → NGINX (443)
2. NGINX → WordPress (9000)
3. WordPress → MariaDB (3306)

## 6. Security Implementation

### Environment Variables
```bash
# .env file structure
DOMAIN_NAME=your.domain.com
MYSQL_ROOT_PASSWORD=secure_root_pw
MYSQL_USER=wordpress_user
MYSQL_PASSWORD=secure_user_pw
```

### SSL/TLS Implementation
- Certificate generation in Dockerfile
- Modern cipher suites only
- Perfect forward secrecy enabled

## 7. Testing Procedures

### Basic Functionality Testing
1. Container Health:
```bash
docker ps --format "table {{.Names}}\t{{.Status}}\t{{.Ports}}"
```

2. HTTPS Verification:
```bash
curl -Ik https://localhost:443
```

### Service Testing Steps
1. WordPress Admin Access:
   - Navigate to https://localhost:443/wp-admin
   - Login with credentials
   - Create test post

2. Database Verification:
```bash
docker exec -it mariadb mysql -u wp_user -p
```

### Volume Testing
1. Data Persistence Test:
```bash
# Create test data
docker-compose down
docker-compose up -d
# Verify data exists
```

### WordPress Site Access

1. Main Website Access:
   - Open browser and navigate to: `https://mafurnic.42.fr`
   - Expected: WordPress site loads (you'll see a security warning for self-signed certificate)
   - Action: Click "Advanced" → "Proceed to site" (wording varies by browser)

2. Admin Panel Access:
   - URL: `https://mafurnic.42.fr/wp-admin`
   - Login Credentials:
     * Username: `supervisor`
     * Password: Check `secrets/credentials.txt`
   - Expected: Successful login to WordPress dashboard

3. Author Account Access:
   - URL: `https://mafurnic.42.fr/wp-admin`
   - Login Credentials:
     * Username: `mafurnic`
     * Password: Check `secrets/credentials.txt`
   - Expected: Successful login with author privileges

### Testing Checklist

1. SSL Certificate:
   - ✓ Browser shows HTTPS (though marked as not trusted due to self-signing)
   - ✓ Certificate details show correct domain
   - ✓ TLS version is 1.2 or 1.3

2. WordPress Functionality:
   - ✓ Create new post (as admin)
   - ✓ Upload media
   - ✓ Install plugin (admin only)
   - ✓ Change theme (admin only)
   - ✓ Create new page
   - ✓ Add comments

3. User Permissions:
   - Admin (supervisor):
     * ✓ Can access dashboard
     * ✓ Can install plugins
     * ✓ Can modify themes
     * ✓ Can manage users
   - Author (mafurnic):
     * ✓ Can access dashboard
     * ✓ Can create posts
     * ✓ Cannot install plugins
     * ✓ Cannot modify themes

4. Performance:
   - ✓ Pages load quickly
   - ✓ Images display correctly
   - ✓ No PHP errors visible
   - ✓ No database connection errors

### Common Issues and Solutions

1. Cannot Access Site:
   ```bash
   # Check if containers are running
   docker ps
   
   # Check NGINX logs
   docker logs nginx
   
   # Verify hosts file
   cat /etc/hosts
   ```

2. Certificate Warnings:
   - Expected behavior with self-signed certificates
   - Verify certificate details in browser:
     * Should match domain name
     * Should be issued to your domain

3. Login Issues:
   ```bash
   # Check WordPress logs
   docker logs wordpress
   
   # Verify database connection
   docker exec wordpress wp db check --allow-root
   ```

4. Database Connection:
   ```bash
   # Check MariaDB status
   docker logs mariadb
   
   # Verify WordPress config
   docker exec wordpress wp config list --allow-root
   ```

### Final Verification Steps

1. Complete Site Test:
   - Access homepage
   - Login as admin
   - Create test post
   - Upload test image
   - Logout
   - Login as author
   - Create another post
   - Verify restrictions

2. Security Verification:
   - Try accessing database port (should fail)
   - Verify only 443 is exposed
   - Check SSL/TLS version
   - Verify admin restrictions

3. Performance Test:
   - Load homepage multiple times
   - Access wp-admin
   - Upload large image
   - Create post with images

4. Cleanup Test:
   ```bash
   # Stop all containers
   docker compose -f srcs/docker-compose.yml down
   
   # Start again
   docker compose -f srcs/docker-compose.yml up -d
   
   # Verify all content persists
   ```

### Expected Results

1. Website Access:
   - HTTPS works (with expected certificate warning)
   - All pages load correctly
   - Images and media work

2. Admin Access:
   - Dashboard accessible
   - All admin functions work
   - Plugin installation works
   - User management works

3. Author Access:
   - Limited dashboard access
   - Can create/edit own posts
   - Cannot access admin functions

4. Data Persistence:
   - Posts remain after container restart
   - Uploads persist
   - User settings maintained

### Database Persistence Testing
1. Initial Setup Verification:
   ```bash
   # Access WordPress and create test content
   - Visit https://mafurnic.42.fr/wp-admin
   - Login as admin
   - Create a new post titled "Persistence Test"
   - Upload a test image
   ```

2. Container Restart Test:
   ```bash
   # Stop all containers
   docker compose -f srcs/docker-compose.yml down

   # Verify containers are stopped
   docker ps

   # Start containers again
   docker compose -f srcs/docker-compose.yml up -d

   # Wait for containers to be healthy
   docker ps  # Check STATUS column
   ```

3. Data Verification Steps:
   - Visit https://mafurnic.42.fr/wp-admin again
   - Login with same credentials
   - Verify:
     * Test post still exists
     * Uploaded image is still available
     * User settings remain unchanged
     * Theme and plugin settings persist

4. Expected Results:
   - All content should remain intact after container restart
   - No database connection errors
   - No need to reinstall WordPress
   - All media files should be accessible

Note: If any data is lost after restart, check:
- Volume mount points
- Database dumps
- WordPress file permissions

## 8. Troubleshooting Guide

### Common Issues
1. Container Startup Failures:
```bash
docker logs nginx    # Check NGINX logs
docker logs wordpress # Check WordPress logs
docker logs mariadb  # Check MariaDB logs
```

2. Network Issues:
```bash
docker network inspect inception_network
```

3. Volume Problems:
```bash
docker volume inspect wordpress_data
docker volume inspect mariadb_data
```

### Quick Fixes
1. Service not starting:
   - Check logs
   - Verify configurations
   - Ensure dependencies are up

2. WordPress issues:
   - Verify database connection
   - Check PHP-FPM status
   - Review error logs

3. Database problems:
   - Check credentials
   - Verify volume permissions
   - Review MariaDB logs 

# Inception Project Evaluation Checklist

## 1. Initial Setup Verification
- [ ] Check that all required files are in the correct directories:
  ```bash
  ls -la srcs/
  ls -la srcs/requirements/
  ls -la srcs/requirements/nginx/
  ls -la srcs/requirements/wordpress/
  ls -la srcs/requirements/mariadb/
  ```

## 2. Docker Configuration Check
- [ ] Verify docker-compose.yml exists and is valid:
  ```bash
  docker compose -f srcs/docker-compose.yml config
  ```
- [ ] Check that all images are built from Debian Buster or Alpine:
  ```bash
  docker image inspect srcs-nginx | grep -i "org.opencontainers.image.base.name"
  docker image inspect srcs-wordpress | grep -i "org.opencontainers.image.base.name"
  docker image inspect srcs-mariadb | grep -i "org.opencontainers.image.base.name"
  ```

## 3. Volume Check
- [ ] Verify volume creation and mounting:
  ```bash
  docker volume ls | grep -E "wordpress|mariadb"
  ls -la /home/mafurnic/data/wordpress/
  ls -la /home/mafurnic/data/mariadb/
  ```

## 4. Network Check
- [ ] Verify custom network creation:
  ```bash
  docker network ls | grep inception
  ```
- [ ] Check network connectivity between containers:
  ```bash
  docker exec wordpress ping -c 2 mariadb
  docker exec wordpress ping -c 2 nginx
  ```

## 5. Container Status Check
- [ ] Verify all containers are running:
  ```bash
  docker ps | grep -E "nginx|wordpress|mariadb"
  ```
- [ ] Check container logs for errors:
  ```bash
  docker logs nginx
  docker logs wordpress
  docker logs mariadb
  ```

## 6. SSL/TLS Check
- [ ] Verify SSL certificate:
  ```bash
  curl -k -vI https://mafurnic.42.fr
  ```
- [ ] Check TLS version (should be 1.2 or 1.3):
  ```bash
  openssl s_client -connect mafurnic.42.fr:443 | grep "Protocol"
  ```

## 7. WordPress Check
- [ ] Test WordPress installation:
  ```bash
  curl -k https://mafurnic.42.fr | grep -i wordpress
  ```
- [ ] Verify WordPress users:
  ```bash
  docker exec wordpress wp user list
  ```
- [ ] Check WordPress configuration:
  ```bash
  docker exec wordpress wp config list
  ```

## 8. Database Check
- [ ] Verify MariaDB is running:
  ```bash
  docker exec mariadb mysqladmin ping -h localhost
  ```
- [ ] Check WordPress database:
  ```bash
  docker exec mariadb mysql -e "SHOW DATABASES;" | grep wordpress
  ```

## 9. NGINX Check
- [ ] Verify NGINX configuration:
  ```bash
  docker exec nginx nginx -t
  ```
- [ ] Check PHP-FPM connection:
  ```bash
  docker exec nginx curl -I wordpress:9000
  ```

## 10. Security Check
- [ ] Verify no root processes in containers:
  ```bash
  docker exec nginx ps aux | grep root
  docker exec wordpress ps aux | grep root
  docker exec mariadb ps aux | grep root
  ```