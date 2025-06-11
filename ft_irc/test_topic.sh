#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Server details
HOST="localhost"
PORT="6667"
PASSWORD="password"

# Function to send commands and receive responses
send_command() {
    echo "$1" | nc -C $HOST $PORT
}

echo -e "${GREEN}Testing TOPIC command...${NC}"

# Test 1: Try to set topic without joining channel
echo -e "\n${GREEN}Test 1: Setting topic without joining channel${NC}"
send_command "PASS $PASSWORD
NICK user1
USER user1 0 * :User 1
TOPIC #test :This should fail"

# Test 2: Create channel and set topic
echo -e "\n${GREEN}Test 2: Create channel and set topic${NC}"
send_command "PASS $PASSWORD
NICK user2
USER user2 0 * :User 2
JOIN #test
TOPIC #test :Welcome to the test channel!"

# Test 3: View current topic
echo -e "\n${GREEN}Test 3: View current topic${NC}"
send_command "PASS $PASSWORD
NICK user3
USER user3 0 * :User 3
JOIN #test
TOPIC #test"

# Test 4: Try to set topic on non-existent channel
echo -e "\n${GREEN}Test 4: Set topic on non-existent channel${NC}"
send_command "PASS $PASSWORD
NICK user4
USER user4 0 * :User 4
TOPIC #nonexistent :This should fail"

# Test 5: Try to view topic without being in channel
echo -e "\n${GREEN}Test 5: View topic without being in channel${NC}"
send_command "PASS $PASSWORD
NICK user5
USER user5 0 * :User 5
TOPIC #test"

echo -e "\n${GREEN}Topic command testing completed${NC}" 