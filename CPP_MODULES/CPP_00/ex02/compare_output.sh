#!/bin/bash

# Run the program and redirect output to a file
./account > output.log

# Compare the output with the expected log file, ignoring timestamps
if diff --ignore-matching-lines='^\[.*\]' output.log 19920104_091532.log > /dev/null; then
    echo "Output matches the expected output."
else
    echo "Output does not match the expected output."
    diff --ignore-matching-lines='^\[.*\]' output.log 19920104_091532.log
fi