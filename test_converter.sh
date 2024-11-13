#!/bin/bash

# Array of test cases
tests=(
    "a"
    "42"
    "-42"
    "42.0f"
    "42.42f"
    "42.0"
    "42.42"
    "0"
    "nan"
    "nanf"
    "+inf"
    "-inf"
    "+inff"
    "-inff"
    "2147483648"
    "-2147483649"
    "abc"
    "0.0f"
    "2147483647"
    "-2147483648"
    "\0"
    "42.4242424242f"
)

# Run each test
for test in "${tests[@]}"
do
    echo "Testing: $test"
    echo "-------------------------"
    ./ScalarConverter "$test"
    echo "-------------------------"
    echo
done 