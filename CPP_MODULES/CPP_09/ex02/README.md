# PmergeMe - Merge-Insert Sort Implementation

## Overview
PmergeMe is a C++98 program that implements the Ford-Johnson algorithm (Merge-insert sort) using two different containers: `std::vector` and `std::deque`. It demonstrates the performance differences between these containers while sorting positive integer sequences.

## Features
- Dual container implementation (vector and deque)
- Hybrid sorting algorithm (merge-insert sort)
- Performance comparison
- Comprehensive error handling
- Time measurement in microseconds

## Program Structure

### Core Components
1. **PmergeMe Class**
   - Two containers: `std::vector<int>` and `std::deque<int>`
   - Sorting algorithms for both containers
   - Time measurement functionality
   - Input validation and error handling

2. **Key Methods**
   - `processInput`: Handles input parsing and validation
   - `mergeInsertSort`: Implements the Ford-Johnson algorithm
   - `insertionSort`: For small sequences (≤ 10 elements)
   - `merge`: For merging sorted sequences

### Sorting Algorithm
The program uses a hybrid approach:
- Merge sort for sequences > 10 elements
- Insertion sort for sequences ≤ 10 elements
- Combines the efficiency of both algorithms

## Program Flow

1. **Input Processing**
   ```cpp
   ./PmergeMe 3 5 1 8 4
   ```

2. **Execution Steps**
   - Parse and validate input numbers
   - Store in both containers
   - Display initial sequence
   - Sort using both containers
   - Measure and compare execution times
   - Display results

3. **Output Format**
   ```
   Before: 3 5 1 8 4
   After:  1 3 4 5 8
   Time to process with std::vector : X.XXXXX us
   Time to process with std::deque  : X.XXXXX us
   ```

## Usage Examples

### Valid Input
```bash
./PmergeMe 5 4 3 2 1
./PmergeMe 9 8 7 6 5 4 3 2 1
./PmergeMe 1 2 3 4 5 6 7 8 9
```

### Error Cases
```bash
./PmergeMe          # Error: no input sequence
./PmergeMe -5 3 2   # Error: negative number
./PmergeMe 3 a 2    # Error: invalid character
./PmergeMe 2147483648  # Error: number too large
```

## Implementation Details

### C++98 Compatibility
- Uses standard containers (vector, deque)
- Traditional error handling
- Standard time measurement

### Algorithm Complexity
- Average case: O(n log n)
- Best case: O(n)
- Worst case: O(n log n)
- Space complexity: O(n)

### Safety Features
1. **Input Validation**
   - Checks for negative numbers
   - Validates numeric format
   - Prevents integer overflow
   - Handles empty inputs

2. **Error Handling**
   - Custom exception class
   - Descriptive error messages
   - Graceful error recovery

## Performance Characteristics

### Vector vs Deque
- Vector: Contiguous memory, better cache performance
- Deque: Segmented memory, better for insertions
- Time measurements in microseconds
- Performance comparison displayed after sorting

### Optimization
- Hybrid algorithm approach
- Threshold-based algorithm selection
- Efficient memory usage
- Minimal copying operations

## Error Prevention
- Complete input validation
- Range checking
- Format verification
- Clear error reporting
- Exception handling

## Performance Metrics
- Displays processing time for both containers
- Microsecond precision
- Direct container performance comparison
- Consistent measurement methodology 