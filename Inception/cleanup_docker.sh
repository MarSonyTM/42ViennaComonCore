#!/bin/bash

# Colors for better readability
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== Docker Cleanup Script for Inception Evaluation ===${NC}"
echo

echo -e "${GREEN}Step 1: Stopping all running Docker containers...${NC}"
CONTAINERS=$(docker ps -q)
if [ -n "$CONTAINERS" ]; then
    docker stop $CONTAINERS
    echo -e "${YELLOW}Containers stopped successfully${NC}"
else
    echo -e "${YELLOW}No running containers found${NC}"
fi
echo

echo -e "${GREEN}Step 2: Removing all Docker containers...${NC}"
CONTAINERS=$(docker ps -qa)
if [ -n "$CONTAINERS" ]; then
    docker rm $CONTAINERS
    echo -e "${YELLOW}Containers removed successfully${NC}"
else
    echo -e "${YELLOW}No containers found to remove${NC}"
fi
echo

echo -e "${GREEN}Step 3: Removing all Docker images...${NC}"
IMAGES=$(docker images -qa)
if [ -n "$IMAGES" ]; then
    docker rmi -f $IMAGES
    echo -e "${YELLOW}Images removed successfully${NC}"
else
    echo -e "${YELLOW}No images found to remove${NC}"
fi
echo

echo -e "${GREEN}Step 4: Removing all Docker volumes...${NC}"
VOLUMES=$(docker volume ls -q)
if [ -n "$VOLUMES" ]; then
    docker volume rm $VOLUMES
    echo -e "${YELLOW}Volumes removed successfully${NC}"
else
    echo -e "${YELLOW}No volumes found to remove${NC}"
fi
echo

echo -e "${GREEN}Step 5: Removing all Docker networks...${NC}"
NETWORKS=$(docker network ls --filter "name=inception" -q)
if [ -n "$NETWORKS" ]; then
    docker network rm $NETWORKS
    echo -e "${YELLOW}Custom networks removed successfully${NC}"
else
    echo -e "${YELLOW}No custom networks found to remove${NC}"
fi
echo

echo -e "${BLUE}=== Docker environment has been cleaned up successfully! ===${NC}"
echo -e "${BLUE}=== Ready to begin Inception evaluation ===${NC}" 