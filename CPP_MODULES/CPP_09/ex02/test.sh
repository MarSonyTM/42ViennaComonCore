#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Compile
echo -e "${BLUE}Compiling...${NC}"
make re

# Function to test sorting
test_sort() {
    local input="$1"
    local description="$2"
    local expected_result="$3"  # "success" or "error"
    
    echo -e "\n${BLUE}Testing: $description${NC}"
    echo "Input: $input"
    
    output=$(./PmergeMe $input 2>&1)
    exit_code=$?
    
    echo "Output:"
    echo "$output"
    
    if [ "$expected_result" = "error" ]; then
        if [ $exit_code -ne 0 ]; then
            echo -e "${GREEN}✓ Test passed (Expected error)${NC}"
        else
            echo -e "${RED}✗ Test failed (Expected error but got success)${NC}"
        fi
    else
        if [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}✓ Test passed${NC}"
        else
            echo -e "${RED}✗ Test failed (Expected success but got error)${NC}"
        fi
    fi
}

# Basic tests from subject
echo -e "\n${YELLOW}=== Basic Tests from Subject ===${NC}"
test_sort "3 5 9 7 4" "Basic test from subject" "success"
test_sort "7 7 * 7 -" "Invalid input from RPN exercise" "error"
test_sort "1 2 * 2 / 2 * 2 4 - +" "Invalid input from RPN exercise" "error"

# Sorting tests
echo -e "\n${YELLOW}=== Sorting Tests ===${NC}"
test_sort "1 2 3 4 5" "Already sorted sequence" "success"
test_sort "5 4 3 2 1" "Reverse sorted sequence" "success"
test_sort "42" "Single number" "success"
test_sort "2 1" "Two numbers" "success"
test_sort "1 3 2 5 4" "Small unsorted sequence" "success"

# Error cases
echo -e "\n${YELLOW}=== Error Cases ===${NC}"
test_sort "-1 2" "Negative number" "error"
test_sort "2 a 3" "Invalid character" "error"
test_sort "" "Empty input" "error"
test_sort "2147483648" "Number too large" "error"
test_sort "1.5 2" "Decimal number" "error"
test_sort "+" "Single operator" "error"
test_sort "1 2 +" "RPN expression" "error"
test_sort "    " "Only spaces" "error"
test_sort "2,3,4" "Wrong separator" "error"
test_sort "2 2" "Duplicate numbers" "success"  # Subject says duplicates handling is up to us

# Performance tests
echo -e "\n${YELLOW}=== Performance Tests ===${NC}"

# Different sizes
test_sort "$(seq 1 10 | tr '\n' ' ')" "10 numbers" "success"
test_sort "$(seq 1 100 | tr '\n' ' ')" "100 numbers" "success"
test_sort "$(seq 1 1000 | tr '\n' ' ')" "1000 numbers" "success"

# Test with 3000 numbers (Linux)
if command -v shuf &> /dev/null; then
    echo -e "\n${BLUE}Testing with 3000 random numbers (Linux)${NC}"
    test_sort "$(shuf -i 1-100000 -n 3000 | tr '\n' ' ')" "3000 random numbers (Linux)" "success"
# Test with 3000 numbers (macOS)
elif command -v jot &> /dev/null; then
    echo -e "\n${BLUE}Testing with 3000 random numbers (macOS)${NC}"
    test_sort "$(jot -r 3000 1 100000 | tr '\n' ' ')" "3000 random numbers (macOS)" "success"
fi

# Edge cases
echo -e "\n${YELLOW}=== Edge Cases ===${NC}"
test_sort "$(seq 1 100 | tr '\n' ' ')" "100 sequential numbers" "success"
test_sort "$(seq 100 -1 1 | tr '\n' ' ')" "100 reverse sequential numbers" "success"
test_sort "$(yes 42 | head -n 50 | tr '\n' ' ')" "50 identical numbers" "success"
test_sort "1 1 1 1 1" "All same numbers" "success"
test_sort "2147483647 1 2" "Max int" "success"
test_sort "0 1 2" "Zero included" "success"
test_sort "1     2     3" "Multiple spaces between numbers" "success"

# Special patterns
echo -e "\n${YELLOW}=== Special Patterns ===${NC}"
test_sort "1 3 5 7 9 2 4 6 8 10" "Alternating pattern" "success"
test_sort "10 9 8 7 6 5 4 3 2 1" "Strictly decreasing" "success"
test_sort "1 2 3 4 5 5 4 3 2 1" "Mountain pattern" "success"
test_sort "1 10 2 9 3 8 4 7 5 6" "Zigzag pattern" "success"

# Stress tests
echo -e "\n${YELLOW}=== Stress Tests ===${NC}"
test_sort "$(seq 1 3000 | sort -R | tr '\n' ' ')" "3000 shuffled sequential numbers" "success"
test_sort "$(for i in {1..3000}; do echo 1; done | tr '\n' ' ')" "3000 identical numbers" "success"
test_sort "$(seq 3000 -1 1 | tr '\n' ' ')" "3000 reverse ordered numbers" "success"

# Cleanup
echo -e "\n${BLUE}Cleaning up...${NC}"
make fclean