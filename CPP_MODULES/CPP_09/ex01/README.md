# Reverse Polish Notation (RPN) Calculator

## Overview
This program implements a Reverse Polish Notation calculator that processes mathematical expressions where operators follow their operands. Built in C++98, it handles basic arithmetic operations while ensuring robust error handling and overflow protection.

## What is RPN?
In RPN (also known as postfix notation), operators follow their operands. This eliminates the need for parentheses:
- Regular notation: `3 + 4` → RPN: `3 4 +`
- Regular notation: `(1 + 2) * 4` → RPN: `1 2 + 4 *`

## Features
- Basic arithmetic operations (+, -, *, /)
- Single-digit number support (0-9)
- Comprehensive error handling
- Integer overflow protection
- Stack-based calculation

## Program Structure

### Core Components
1. **RPN Class**
   - Main container: `std::stack<int>` for operand storage
   - Helper methods for validation and operations
   - Custom exception class for error handling

2. **Key Methods**
   - `calculate`: Processes the RPN expression
   - `performOperation`: Executes arithmetic operations
   - `isOperator`: Validates operators
   - `isValidNumber`: Checks number validity

### Error Handling
- **Types of Errors Caught**:
  - Insufficient operands
  - Division by zero
  - Numbers >= 10
  - Invalid tokens
  - Integer overflow
  - Wrong number of operators

## Program Flow

1. **Input Processing**
   ```cpp
   ./RPN "expression"
   ```

2. **Calculation Process**
   - Tokenize input string
   - For each token:
     - If number: push to stack
     - If operator: pop operands, perform operation, push result
   - Return final result

3. **Error Checking**
   - Validate input format
   - Check for stack underflow/overflow
   - Verify operation validity
   - Protect against integer overflow

## Usage Examples

### Valid Inputs
```bash
./RPN "1 2 +"        # Output: 3
./RPN "3 4 * 5 +"    # Output: 17
./RPN "7 7 * 7 -"    # Output: 42
```

### Error Cases
```bash
./RPN "1 2"          # Error: wrong number of operators
./RPN "1 10 +"       # Error: number >= 10
./RPN "1 / 0"        # Error: division by zero
./RPN "1 2 + +"      # Error: insufficient operands
```

## Implementation Details

### C++98 Compatibility
- Uses standard container `std::stack`
- Traditional error handling with exceptions
- Standard I/O operations

### Safety Features
1. **Overflow Protection**
   - Checks for integer overflow in all operations
   - Validates operation results
   - Prevents undefined behavior

2. **Input Validation**
   - Ensures proper token format
   - Validates number range
   - Verifies operator validity

3. **Stack Safety**
   - Checks for stack underflow
   - Ensures proper operand count
   - Validates final result

## Error Prevention
- Validates all input formats
- Checks operation validity
- Verifies numeric ranges
- Provides clear error messages
- Maintains stack integrity

## Performance
- O(n) time complexity for expression processing
- Efficient stack-based operations
- Minimal memory usage
- Robust error handling 