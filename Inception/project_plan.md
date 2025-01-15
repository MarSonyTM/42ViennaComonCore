# Inception Project Plan

## Phase 1: Setup & Infrastructure (Day 1)
### 1. Initial Setup
- Create project structure
- Setup basic Makefile
- Create .env file for environment variables
- Setup basic docker-compose.yml

### 2. Network Configuration
- Create Docker network
- Configure domain (login.42.fr)
- Setup SSL certificates

## Phase 2: Core Services (Days 2-3)
### 1. NGINX Container
- Write Dockerfile
- Configure TLS
- Setup reverse proxy
- Test connectivity

### 2. MariaDB Container
- Write Dockerfile
- Setup database initialization
- Configure persistence
- Setup users and permissions

### 3. WordPress Container
- Write Dockerfile
- Configure php-fpm
- Setup WordPress files
- Connect to MariaDB

## Phase 3: Integration & Volumes (Day 4)
### 1. Volume Setup
- WordPress files volume
- Database volume
- Configure persistence

### 2. Service Integration
- Connect all services
- Test full workflow
- Debug connections

## Phase 4: Bonus Features (Days 5-6)
### 1. Redis Cache
- Setup Redis container
- Configure WordPress integration

### 2. FTP Server
- Setup vsftpd
- Configure access to WordPress volume

### 3. Static Website
- Choose framework/language
- Create simple site
- Configure NGINX for it

### 4. Adminer
- Setup container
- Configure database access

### 5. Additional Service
- TBD based on preference

## Phase 5: Testing & Documentation (Day 7)
### 1. Testing
- Full integration testing
- Security testing
- Performance testing

### 2. Documentation
- Write setup instructions
- Document configurations
- Create troubleshooting guide

## Platform Considerations
### Mac vs Linux Differences
- Docker on Mac runs through Docker Desktop (VM layer)
- Performance might vary
- File system permissions behave differently
- Network handling varies

### Compatibility Strategy
- Use Docker Compose for platform abstraction
- Keep configurations platform-agnostic
- Use environment variables for platform-specific settings
- Test on both platforms if possible
- Maintain detailed documentation 