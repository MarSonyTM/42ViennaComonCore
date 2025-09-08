#!/bin/bash

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}🔍 Testing database setup...${NC}\n"

# Navigate to backend directory
cd backend

# Run migrations
echo "Running database migrations..."
if npx knex migrate:latest; then
    echo -e "${GREEN}✅ Migrations completed successfully${NC}"
else
    echo -e "${RED}❌ Migration failed${NC}"
    exit 1
fi

# Insert test data
echo -e "\nInserting test data..."
if node src/database/test-data.js; then
    echo -e "\n${GREEN}✨ Database setup and test data verification completed successfully!${NC}"
else
    echo -e "\n${RED}❌ Database test failed${NC}"
    exit 1
fi