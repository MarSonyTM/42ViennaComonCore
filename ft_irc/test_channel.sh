#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Test configuration
SERVER="localhost"
PORT="6667"
PASSWORD="password"
CHANNEL="#testchannel"

# Function to print test status
print_status() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}[✓] $2${NC}"
    else
        echo -e "${RED}[✗] $2${NC}"
        exit 1
    fi
}

# Kill any existing ircserv
pkill ircserv

# Start the server
./ircserv $PORT $PASSWORD &
SERVER_PID=$!
sleep 1

print_status $? "Server started on port $PORT"

# Test 1: Connect first client and register
echo "PASS $PASSWORD" | nc -w 1 $SERVER $PORT
print_status $? "Test 1: First client can connect"

# Test 2: Join channel
(
echo "PASS $PASSWORD"
echo "NICK user1"
echo "USER user1 0 * :User One"
sleep 1
echo "JOIN $CHANNEL"
sleep 1
) | nc -w 3 $SERVER $PORT
print_status $? "Test 2: First client can join channel"

# Test 3: Second client joins
(
echo "PASS $PASSWORD"
echo "NICK user2"
echo "USER user2 0 * :User Two"
sleep 1
echo "JOIN $CHANNEL"
sleep 1
) | nc -w 3 $SERVER $PORT
print_status $? "Test 3: Second client can join channel"

# Test 4: Send message to channel
(
echo "PASS $PASSWORD"
echo "NICK user3"
echo "USER user3 0 * :User Three"
sleep 1
echo "JOIN $CHANNEL"
sleep 1
echo "PRIVMSG $CHANNEL :Hello channel!"
sleep 1
) | nc -w 4 $SERVER $PORT
print_status $? "Test 4: Can send message to channel"

# Test 5: Part channel
(
echo "PASS $PASSWORD"
echo "NICK user4"
echo "USER user4 0 * :User Four"
sleep 1
echo "JOIN $CHANNEL"
sleep 1
echo "PART $CHANNEL"
sleep 1
) | nc -w 4 $SERVER $PORT
print_status $? "Test 5: Can part from channel"

# Cleanup
kill $SERVER_PID
print_status $? "Cleanup completed"

echo -e "${GREEN}All tests completed!${NC}" 