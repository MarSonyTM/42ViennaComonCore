# Inception Project Todo List

## Environment Setup Notes
- [x] Project can be developed on both school computers and personal Mac
- [x] Requires VM setup in both environments
  - [x] Virtual Machine with Ubuntu 24.04.1 LTS is set up
  - [ ] Docker installation pending
  - [ ] Docker Compose installation pending
- [ ] When moving between environments:
  1. Clone Git repository
  2. Rebuild Docker images
  3. Recreate volumes
  4. No need to rewrite configurations

## Detailed Todo List

### 1. Initial Setup
- [x] Create Virtual Machine
  - [x] Ubuntu (x86_64 version) - Running Ubuntu 24.04.1 LTS
  - [x] Sufficient resources (CPU, RAM, Storage)
  - [ ] Docker and Docker Compose installed
- [ ] Create Project Structure:
```
Inception/
├── Makefile
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

### 2. Environment Configuration
- [ ] Create `.env` file with:
  - Domain name (login.42.fr)
  - MySQL credentials
  - WordPress settings
  - SSL certificate paths
- [ ] Setup secrets management
  - Ensure no credentials in Dockerfiles
  - Use Docker secrets for sensitive data
- [ ] Configure domain name (login.42.fr -> local IP)

### 3. NGINX Setup
- [ ] Create Dockerfile
  - Use penultimate stable Alpine/Debian
  - No latest tag
- [ ] SSL/TLS Configuration
  - TLSv1.2 or TLSv1.3 only
  - Port 443 only
- [ ] Reverse Proxy Setup
  - Forward to WordPress container
  - Handle SSL termination

### 4. MariaDB Setup
- [ ] Create Dockerfile
  - Use penultimate stable Alpine/Debian
  - No latest tag
- [ ] Database Configuration
  - Initialize database
  - Create required users
  - Set up secure passwords
- [ ] Volume Setup
  - Configure persistence
  - Set correct permissions

### 5. WordPress Setup
- [ ] Create Dockerfile
  - Use penultimate stable Alpine/Debian
  - No latest tag
- [ ] PHP-FPM Configuration
  - Install and configure php-fpm
  - Optimize settings
- [ ] WordPress Setup
  - Install WordPress files
  - Configure wp-config.php
- [ ] Volume Configuration
  - Website files persistence
  - Correct permissions

### 6. Network & Volumes
- [ ] Docker Network
  - Create custom network
  - No host network usage
  - No links allowed
- [ ] Volume Setup
  - WordPress files in /home/login/data
  - MariaDB data in /home/login/data
  - Proper permissions and ownership

### 7. Security & Best Practices
- [ ] Environment Variables
  - Move all credentials to .env
  - Use Docker secrets where appropriate
- [ ] Container Configuration
  - Proper restart policies
  - No infinite loops
  - No hacky solutions (tail -f, sleep infinity, etc.)
- [ ] Process Management
  - Understand PID 1
  - Proper daemon usage
  - Clean shutdown handling

### 8. Testing & Verification
- [ ] Container Tests
  - Crash recovery
  - Proper startup
  - Clean shutdown
- [ ] Functionality Tests
  - SSL/TLS verification
  - WordPress access
  - Database persistence
  - File persistence
- [ ] Security Tests
  - No exposed passwords
  - Proper network isolation
  - SSL/TLS configuration

### 9. Optional Bonus Features
- [ ] Redis Cache
  - Setup container
  - Configure WordPress integration
- [ ] FTP Server
  - Setup vsftpd
  - Configure WordPress volume access
- [ ] Static Website
  - Choose non-PHP language
  - Create simple site
- [ ] Adminer
  - Setup container
  - Configure database access
- [ ] Additional Service
  - Choose useful service
  - Prepare justification

### 10. Documentation & Submission
- [ ] Documentation
  - Setup instructions
  - Configuration details
  - Troubleshooting guide
- [ ] Code Cleanup
  - Remove unnecessary files
  - Clean up configurations
- [ ] Structure Verification
  - Check folder names
  - Verify file permissions
- [ ] Git Repository
  - Clean commit history
  - No credentials in repo
  - Ready for peer review

## Important Rules to Remember
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

## Next Steps:
1. Install Docker and Docker Compose
2. Create the basic project structure
3. Set up initial configuration files (Makefile, .env, docker-compose.yml)
4. Begin service configuration starting with NGINX 