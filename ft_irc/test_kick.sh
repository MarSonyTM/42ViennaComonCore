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
        echo -e "${RED}[✗] $2 (Exit code: $1)${NC}"
        echo "Last output:"
        cat /tmp/last_output.txt
        exit 1
    fi
}

# Kill any existing ircserv
pkill ircserv

# Start the server
./ircserv $PORT $PASSWORD &
SERVER_PID=$!
sleep 2

print_status $? "Server started on port $PORT"

# Test 1: Create channel and make first user operator
rm -f /tmp/last_output.txt
(
echo -ne "PASS $PASSWORD\r\n"
sleep 1
echo -ne "NICK operator\r\n"
sleep 1
echo -ne "USER operator 0 * :Channel Operator\r\n"
sleep 1
echo -ne "JOIN $CHANNEL\r\n"
sleep 2
) | nc $SERVER $PORT | tee /tmp/last_output.txt

cat /tmp/last_output.txt | grep -i "join.*#testchannel" > /dev/null
print_status $? "Test 1: Channel operator setup"

# Test 2: Join with target user
rm -f /tmp/last_output.txt
(
echo -ne "PASS $PASSWORD\r\n"
sleep 1
echo -ne "NICK target\r\n"
sleep 1
echo -ne "USER target 0 * :Target User\r\n"
sleep 1
echo -ne "JOIN $CHANNEL\r\n"
sleep 2
) | nc $SERVER $PORT | tee /tmp/last_output.txt

echo "Test 2 output:"
cat /tmp/last_output.txt
cat /tmp/last_output.txt | grep -i "join.*#testchannel" > /dev/null
print_status $? "Test 2: Target user joined"

# Test 3: Try to kick as non-operator
rm -f /tmp/last_output.txt
(
echo -ne "PASS $PASSWORD\r\n"
sleep 1
echo -ne "NICK nonop\r\n"
sleep 1
echo -ne "USER nonop 0 * :Non Operator\r\n"
sleep 1
echo -ne "JOIN $CHANNEL\r\n"
sleep 1
echo -ne "KICK $CHANNEL target :trying to kick\r\n"
sleep 2
) | nc $SERVER $PORT | tee /tmp/last_output.txt

echo "Test 3 output:"
cat /tmp/last_output.txt
cat /tmp/last_output.txt | grep -i "482" > /dev/null
print_status $? "Test 3: Non-operator cannot kick"

# Test 4: Operator kicks target
rm -f /tmp/last_output.txt
(
echo -ne "PASS $PASSWORD\r\n"
sleep 1
echo -ne "NICK operator2\r\n"
sleep 1
echo -ne "USER operator2 0 * :Channel Operator\r\n"
sleep 1
echo -ne "JOIN $CHANNEL\r\n"
sleep 1
echo -ne "KICK $CHANNEL target :kicked by operator\r\n"
sleep 2
) | nc $SERVER $PORT | tee /tmp/last_output.txt

echo "Test 4 output:"
cat /tmp/last_output.txt
cat /tmp/last_output.txt | grep -i "kick.*#testchannel.*target" > /dev/null
print_status $? "Test 4: Operator can kick user"

# Test 5: Try to kick non-existent user
rm -f /tmp/last_output.txt
(
echo -ne "PASS $PASSWORD\r\n"
sleep 1
echo -ne "NICK operator3\r\n"
sleep 1
echo -ne "USER operator3 0 * :Channel Operator\r\n"
sleep 1
echo -ne "JOIN $CHANNEL\r\n"
sleep 1
echo -ne "KICK $CHANNEL nonexistent :kicking nobody\r\n"
sleep 2
) | nc $SERVER $PORT | tee /tmp/last_output.txt

echo "Test 5 output:"
cat /tmp/last_output.txt
cat /tmp/last_output.txt | grep -i "401" > /dev/null
print_status $? "Test 5: Cannot kick non-existent user"

# Cleanup
kill $SERVER_PID
rm -f /tmp/last_output.txt
print_status $? "Cleanup completed"

echo -e "${GREEN}All tests completed!${NC}" 