# Bitcoin Exchange Calculator

## Overview
This program is a Bitcoin price calculator that processes historical Bitcoin exchange rates and calculates values based on input requests. It's implemented in C++98 and handles Bitcoin exchange rates from 2009 to 2022.

## Features
- Reads historical Bitcoin exchange rates from a database file
- Processes input requests to calculate Bitcoin values
- Handles dates between 2009-2022
- Validates exchange rates up to 66063.56 (highest historical value)
- Provides detailed error handling and messages

## Program Structure

### Core Components
1. **BitcoinExchange Class**
   - Main container: `std::map<std::string, double>` for date->price mapping
   - Static constant: `MAX_ALLOWED_VALUE` (66063.56)
   - Custom exception classes for error handling

2. **Key Methods**
   - `loadDatabase`: Processes the exchange rate database
   - `processInputFile`: Handles input calculations
   - `isValidDate`: Validates date formats and ranges
   - `findClosestDate`: Locates exact or nearest previous date
   - `getExchangeRate`: Retrieves exchange rates

### Error Handling
- **Custom Exceptions**:
  - FileError: File operation issues
  - DateError: Invalid date formats/ranges
  - ValueError: Invalid numeric values

- **Error Messages**:
  - "Error: could not open file"
  - "Error: bad input"
  - "Error: not a positive number"
  - "Error: too large a number"

## Program Flow

1. **Program Start**
   ```cpp
   ./btc input.txt
   ```

2. **Initialization**
   - Verify input file argument
   - Create BitcoinExchange object
   - Load database (data.csv)

3. **Database Loading**
   - Open data.csv
   - Skip header
   - Process and validate each line
   - Store valid exchange rates

4. **Input Processing**
   - Open input file
   - For each line:
     - Validate format (date | value)
     - Check date validity
     - Verify value range (0-1000)
     - Calculate using exchange rate
     - Display result or error

## Usage

### Input Format
```
date | value
```

### Example
Input:
```
2011-01-03 | 3
```
Output:
```
2011-01-03 => 3 = 0.9
```

### Error Examples
1. Invalid date:
   ```
   2008-01-03 | 3
   Error: bad input => 2008-01-03 | 3
   ```

2. Negative value:
   ```
   2011-01-03 | -3
   Error: not a positive number
   ```

3. Excessive value:
   ```
   2011-01-03 | 2000
   Error: too large a number
   ```

## Implementation Details

### C++98 Compatibility
- Uses traditional C++ features
- Custom string conversion functions
- Standard file I/O methods

### Data Structures
- `std::map` for O(log n) date lookup
- String handling for dates and values
- Exception hierarchy for error management

### Key Features
- Maintains input precision
- Uses fixed 2 decimal places for results
- Handles floating-point calculations safely

## Error Prevention
- Validates all input formats
- Checks date ranges and formats
- Verifies value ranges
- Provides clear error messages
- Maintains data integrity

## Performance
- O(log n) complexity for date lookups
- Efficient string handling
- Minimal memory usage
- Robust error handling 