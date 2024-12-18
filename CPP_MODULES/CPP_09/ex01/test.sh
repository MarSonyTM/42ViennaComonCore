# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 12:31:01 by marianfurni       #+#    #+#              #
#    Updated: 2024/12/18 15:13:43 by marianfurni      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Compile
printf "${BLUE}Compiling...${NC}\n"
make re

# Function to test RPN expression
test_rpn() {
    local expression="$1"
    local expected="$2"
    local description="$3"
    
    printf "\n${BLUE}Testing: %s${NC}\n" "$description"
    printf "Expression: %s\n" "$expression"
    printf "Expected: %s\n" "$expected"
    
    result=$(./RPN "$expression" 2>&1)
    printf "Got: %s\n" "$result"
    
    if [ "$expected" = "Error" ]; then
        case "$result" in
            Error:*) printf "${GREEN}✓ Test passed${NC}\n" ;;
            *) printf "${RED}✗ Test failed${NC}\n" ;;
        esac
    elif [ "$result" = "$expected" ]; then
        printf "${GREEN}✓ Test passed${NC}\n"
    else
        printf "${RED}✗ Test failed${NC}\n"
    fi
}

# Basic tests from subject
printf "\n${BLUE}=== Basic Tests from Subject ===${NC}\n"
test_rpn "8 9 * 9 - 9 - 9 - 4 - 1 +" "42" "Basic test 1"
test_rpn "7 7 * 7 -" "42" "Basic test 2"
test_rpn "1 2 * 2 / 2 * 2 4 - +" "0" "Basic test 3"

# Advanced tests
printf "\n${BLUE}=== Advanced Tests ===${NC}\n"
test_rpn "9 8 * 4 * 4 / 2 + 9 - 8 - 8 - 1 - 6 -" "42" "Complex expression 1"
test_rpn "1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 /" "15" "Complex expression 2"

# Additional Complex Operations
printf "\n${BLUE}=== Additional Complex Operations ===${NC}\n"
test_rpn "3 4 + 5 * 7 2 - *" "175" "Multiple operations with precedence"
test_rpn "9 8 7 6 5 4 3 2 1 * * * * * * * *" "362880" "Long multiplication chain"
test_rpn "1 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 +" "45" "Long addition chain"
test_rpn "9 8 - 7 - 6 - 5 - 4 - 3 - 2 - 1 -" "-27" "Long subtraction chain"
test_rpn "8 4 2 / /" "4" "Division chain"

# Specific Overflow Tests
printf "\n${BLUE}=== Specific Overflow Tests ===${NC}\n"
test_rpn "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *" "Error" "Large multiplication overflow"
test_rpn "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *" "Error" "Sequential multiplication overflow"
test_rpn "9 9 * 9 * 9 * 9 * 9 * 9 * 9 *" "Error" "Mixed multiplication overflow"

# Division special cases
test_rpn "5 0 /" "Error" "Division by zero"
test_rpn "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 0 /" "Error" "Division by zero after overflow"

# Mixed overflow cases
test_rpn "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 +" "Error" "Addition after overflow"
test_rpn "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 -" "Error" "Subtraction after overflow"

# Large number operations (not overflow)
test_rpn "9 9 * 9 * 9 * 9 * 9 * 2 +" "531443" "Large number addition"
test_rpn "9 9 * 9 * 9 * 9 * 9 * 2 -" "531439" "Large number subtraction"

# Comprehensive Error Cases
printf "\n${BLUE}=== Comprehensive Error Cases ===${NC}\n"
test_rpn "(1 + 1)" "Error" "Parentheses not allowed"
test_rpn "1 2 3 +" "Error" "Too many operands"
test_rpn "1 +" "Error" "Not enough operands"
test_rpn "1 2 &" "Error" "Invalid operator"
test_rpn "" "Error" "Empty expression"
test_rpn "10 2 +" "Error" "Number >= 10"
test_rpn "5 0 /" "Error" "Division by zero"
test_rpn "1 2 + +" "Error" "Too many operators"
test_rpn "1.5 2 +" "Error" "Decimal numbers"
test_rpn "a b +" "Error" "Invalid characters"
test_rpn "+" "Error" "Only operator"
test_rpn "1 2" "Error" "Only numbers, no operator"
test_rpn "* * *" "Error" "Only operators, no numbers"
test_rpn "1 + 2" "Error" "Infix notation instead of RPN"
test_rpn "1 2+" "Error" "No spaces between tokens"
test_rpn "  " "Error" "Only spaces"

# Edge Cases and Boundary Tests
printf "\n${BLUE}=== Edge Cases and Boundary Tests ===${NC}\n"
test_rpn "0 0 +" "0" "Zero addition"
test_rpn "0 1 /" "0" "Zero divided by number"
test_rpn "9 9 *" "81" "Maximum valid numbers"
test_rpn "1 2 + 3 + 4 + 5 +" "15" "Multiple operations"
test_rpn "9 1 -" "8" "Simple subtraction"
test_rpn "2 3 * 4 *" "24" "Multiple multiplications"

# Mixed Operations Tests
printf "\n${BLUE}=== Mixed Operations Tests ===${NC}\n"
test_rpn "3 4 + 5 * 2 /" "17" "Mixed arithmetic 1"
test_rpn "9 3 / 2 * 4 +" "10" "Mixed arithmetic 2"
test_rpn "5 3 - 4 * 2 /" "4" "Mixed arithmetic 3"
test_rpn "1 2 + 3 * 4 - 5 +" "10" "Mixed arithmetic 4"
test_rpn "7 3 * 5 + 2 - 4 /" "6" "Mixed arithmetic 5"

# Cleanup
printf "\n${BLUE}Cleaning up...${NC}\n"
make fclean