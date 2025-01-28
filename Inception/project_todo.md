# Inception Project Todo List

## Environment Setup Notes
- [x] Project can be developed on both school computers and personal Mac
- [x] Requires VM setup in both environments
  - [x] Virtual Machine with Ubuntu 24.04.1 LTS is set up
  - [x] Docker installation completed (version 26.1.3)
  - [x] Docker Compose installation completed (version 2.27.1)
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
  - [x] Docker and Docker Compose installed
- [x] Create Project Structure:
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
- [x] Create `.env` file with:
  - Domain name (login.42.fr)
  - MySQL credentials
  - WordPress settings
  - SSL certificate paths
- [x] Setup secrets management
  - Ensure no credentials in Dockerfiles
  - Use Docker secrets for sensitive data
- [ ] Configure domain name (login.42.fr -> local IP)

### 3. NGINX Setup
- [x] Create Dockerfile
  - [x] Use penultimate stable Alpine/Debian (Alpine 3.17)
  - [x] No latest tag
- [x] SSL/TLS Configuration
  - [x] TLSv1.2 or TLSv1.3 only
  - [x] Port 443 only
- [x] Reverse Proxy Setup
  - [x] Forward to WordPress container
  - [x] Handle SSL termination

### 4. MariaDB Setup
- [x] Create Dockerfile
  - [x] Use penultimate stable Alpine/Debian (Alpine 3.17)
  - [x] No latest tag
- [x] Database Configuration
  - [x] Initialize database
  - [x] Create required users
  - [x] Set up secure passwords
- [x] Volume Setup
  - [x] Configure persistence
  - [x] Set correct permissions

### 5. WordPress Setup
- [x] Create Dockerfile
  - [x] Use penultimate stable Alpine/Debian (Alpine 3.17)
  - [x] No latest tag
- [x] PHP-FPM Configuration
  - [x] Install and configure php-fpm
  - [x] Optimize settings
- [x] WordPress Setup
  - [x] Install WordPress files
  - [x] Configure wp-config.php
- [x] Volume Configuration
  - [x] Website files persistence
  - [x] Correct permissions

### 6. Network & Volumes
- [x] Docker Network
  - [x] Create custom network
  - [x] No host network usage
  - [x] No links allowed
- [x] Volume Setup
  - [x] WordPress files in /home/login/data
  - [x] MariaDB data in /home/login/data
  - [x] Proper permissions and ownership

### 7. Security & Best Practices
- [x] Environment Variables
  - [x] Move all credentials to .env
  - [x] Use Docker secrets where appropriate
- [x] Container Configuration
  - [x] Proper restart policies
  - [x] No infinite loops
  - [x] No hacky solutions (tail -f, sleep infinity, etc.)
- [x] Process Management
  - [x] Understand PID 1
  - [x] Proper daemon usage
  - [x] Clean shutdown handling

### 8. Testing & Verification
- [x] Container Tests
  - [x] Proper startup
  - [x] Clean shutdown
  - [x] Crash recovery (using unless-stopped policy)
- [x] Functionality Tests
  - [x] SSL/TLS verification (TLSv1.2/1.3)
  - [x] WordPress access
  - [x] Database persistence
  - [x] File persistence
- [x] Security Tests
  - [x] No exposed passwords
  - [x] Proper network isolation
  - [x] SSL/TLS configuration

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
1. ~~Install Docker and Docker Compose~~ ✓
2. ~~Create the basic project structure~~ ✓
3. Set up initial configuration files:
   - ~~Create basic Makefile~~ ✓
   - Configure .env file (Next)
     * Domain name (login.42.fr)
     * MySQL credentials
     * WordPress settings
     * SSL certificate paths
   - Set up docker-compose.yml
4. Begin service configuration starting with NGINX 

## Current Progress (Last Updated):
- Environment setup complete
- Project structure created
- Makefile created with all necessary targets
- README.md created with command documentation
- Environment variables and secrets configured
- MariaDB container configured and working
- WordPress container configured and working
- NGINX container configured and working
- All mandatory requirements verified and working
- Next task: Update README with comprehensive documentation 