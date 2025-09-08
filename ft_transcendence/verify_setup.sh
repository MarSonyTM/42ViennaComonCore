#!/bin/bash

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}🔍 Running comprehensive setup verification...${NC}\n"

# Function to check if a command exists
check_command() {
    if ! command -v $1 &> /dev/null; then
        echo -e "${RED}❌ $1 is not installed${NC}"
        return 1
    else
        echo -e "${GREEN}✅ $1 is installed${NC}"
        return 0
    fi
}

# Function to check if a file exists and is not empty
check_file() {
    if [ ! -f "$1" ]; then
        echo -e "${RED}❌ $1 is missing${NC}"
        return 1
    elif [ ! -s "$1" ]; then
        echo -e "${RED}❌ $1 is empty${NC}"
        return 1
    else
        echo -e "${GREEN}✅ $1 exists and has content${NC}"
        return 0
    fi
}

# Function to check if a directory exists
check_directory() {
    if [ ! -d "$1" ]; then
        echo -e "${RED}❌ Directory $1 is missing${NC}"
        return 1
    else
        echo -e "${GREEN}✅ Directory $1 exists${NC}"
        return 0
    fi
}

# Function to check npm package.json
check_package_json() {
    local dir=$1
    if ! jq . "${dir}/package.json" >/dev/null 2>&1; then
        echo -e "${RED}❌ ${dir}/package.json is not valid JSON${NC}"
        return 1
    else
        echo -e "${GREEN}✅ ${dir}/package.json is valid${NC}"
        return 0
    fi
}

echo "1. Checking required tools..."
check_command "docker"
check_command "docker-compose"
check_command "node"
check_command "npm"

echo -e "\n2. Checking project structure..."
check_directory "frontend"
check_directory "backend"
check_directory "database"

echo -e "\n3. Checking configuration files..."
check_file "docker-compose.yml"
check_file "frontend/Dockerfile"
check_file "backend/Dockerfile"
check_file "frontend/package.json"
check_file "backend/package.json"
check_file "frontend/tsconfig.json"
check_file "backend/tsconfig.json"

echo -e "\n4. Validating package.json files..."
check_package_json "frontend"
check_package_json "backend"

echo -e "\n5. Checking Docker configuration..."
# Stop any existing containers
docker-compose down &>/dev/null

echo "Building containers..."
if ! docker-compose build --no-cache; then
    echo -e "${RED}❌ Docker build failed${NC}"
    exit 1
fi

echo "Starting containers..."
if ! docker-compose up -d; then
    echo -e "${RED}❌ Docker containers failed to start${NC}"
    exit 1
fi

# Wait for services to be ready
echo "Waiting for services to start..."
sleep 10

echo -e "\n6. Testing backend health..."
if curl -s http://localhost:3001/health | grep -q "ok"; then
    echo -e "${GREEN}✅ Backend health check passed${NC}"
else
    echo -e "${RED}❌ Backend health check failed${NC}"
    docker-compose logs backend
    docker-compose down
    exit 1
fi

echo -e "\n7. Testing frontend accessibility..."
if curl -s http://localhost:3000 | grep -q "ft_transcendence"; then
    echo -e "${GREEN}✅ Frontend accessibility check passed${NC}"
else
    echo -e "${RED}❌ Frontend accessibility check failed${NC}"
    docker-compose logs frontend
    docker-compose down
    exit 1
fi

echo -e "\n8. Checking container logs for errors..."
if docker-compose logs | grep -i "error"; then
    echo -e "${YELLOW}⚠️  Found potential errors in logs${NC}"
else
    echo -e "${GREEN}✅ No obvious errors in container logs${NC}"
fi

echo -e "\n9. Testing container networking..."
if docker-compose exec backend ping -c 1 frontend &>/dev/null; then
    echo -e "${GREEN}✅ Container networking is working${NC}"
else
    echo -e "${RED}❌ Container networking check failed${NC}"
fi

echo -e "\n10. Checking resource usage..."
docker stats --no-stream

echo -e "\n${YELLOW}Verification complete!${NC}"
echo "Use 'docker-compose down' to stop the containers when finished."
