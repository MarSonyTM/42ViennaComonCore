/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:23:17 by marianfurni       #+#    #+#             */
/*   Updated: 2024/12/20 11:11:03 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cstdlib> // std::atoi, std::strtod
#include <iostream> // std::cout, std::cerr
#include <cerrno> // std::errno
#include <sstream> // std::ostringstream

// Helper function declaration to convert double to string for error messages
std::string doubleToString(double value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// Define the static member
const double BitcoinExchange::MAX_ALLOWED_VALUE = 66063.56;

// Orthodox Canonical Form implementations
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& database_file) {
    loadDatabase(database_file);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _database(other._database) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _database = other._database;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// Private helper methods
bool BitcoinExchange::isValidDate(const std::string& date) const {
    // Check length and forma (yyyy-mm-dd)
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    // Check if all other characters are digits exept for dashes
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7 && !std::isdigit(date[i])) // check if the character is not a digit and not the separator
            return false;
    }

    try {
        // extract year, month, day from date
        int year = std::atoi(date.substr(0, 4).c_str());
        int month = std::atoi(date.substr(5, 2).c_str());
        int day = std::atoi(date.substr(8, 2).c_str());

        // Check year range (Bitcoin started in 2009)
        if (year < 2009) return false;
        
        // Check for future dates (using 2022 as the limit based on data.csv)
        if (year > 2022) return false;

        // Check month range
        if (month < 1 || month > 12) return false;

        // Check days per month
        const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int maxDays = daysInMonth[month];

        // Adjust February for leap years
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
            maxDays = 29;

        if (day < 1 || day > maxDays)
            return false;

        return true;
    } catch (...) {
        return false;
    }
}

void BitcoinExchange::loadDatabase(const std::string& filename) {
    // Open the database file
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw FileError("Error: could not open database file.");
    }

    std::string line;
    bool hasData = false;

    // Skip header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty() || line.find_first_not_of(" \t\n\r") == std::string::npos)
            continue;

        // Find comma position
        size_t comma_pos = line.find(',');
        if (comma_pos == std::string::npos) {
            throw FileError("Error: database bad input => " + line);
        }

        // Split into date and value
        std::string date = line.substr(0, comma_pos);
        std::string value_str = line.substr(comma_pos + 1);

        // Trim whitespace
        while (!date.empty() && std::isspace(date[0]))
            date.erase(0, 1);
        while (!date.empty() && std::isspace(date[date.length() - 1]))
            date.erase(date.length() - 1);
        while (!value_str.empty() && std::isspace(value_str[0]))
            value_str.erase(0, 1);
        while (!value_str.empty() && std::isspace(value_str[value_str.length() - 1]))
            value_str.erase(value_str.length() - 1);

        // Validate date format
        if (!isValidDate(date)) {
            throw FileError("Error: bad input => " + line);
        }

        // Validate and convert exchange rate
        char* end;
        errno = 0;  // Reset errno before conversion
        double value = std::strtod(value_str.c_str(), &end);
        if (*end != '\0' || value_str.empty() || errno == ERANGE) {
            throw FileError("Error: bad input => " + line);
        }

        // Validate exchange rate value
        if (value < 0) {
            throw FileError("Error: not a positive number => " + line);
        }

        // Check if the value exceeds the maximum allowed value
        if (value > MAX_ALLOWED_VALUE) {
            throw FileError("Error: unrealistic exchange rate (max allowed: " + doubleToString(MAX_ALLOWED_VALUE) + ") => " + line);
        }

        _database[date] = value;
        hasData = true;
    }

    if (!hasData) {
        throw FileError("Error: empty database file.");
    }
}

std::string BitcoinExchange::findClosestDate(const std::string& date) const {
    std::map<std::string, double>::const_iterator it = _database.lower_bound(date);
    
    if (it == _database.begin()) {
        return it->first;
    }
    
    if (it == _database.end() || it->first != date) {
        --it;
    }
    
    return it->first;
}

double BitcoinExchange::getExchangeRate(const std::string& date) const {
    if (_database.empty()) {
        throw DateError("No exchange rate data available");
    }

    std::string closest_date = findClosestDate(date);
    double rate = _database.at(closest_date);
    if (closest_date != date) {
        std::cerr << "Warning: Using rate " << rate << " from " << closest_date << " instead of " << date << std::endl;
    }
    return rate;
}

bool BitcoinExchange::isValidNumber(const std::string& str) const
{
    if (str.empty())
        return false;
    
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isdigit(str[i]) && str[i] != '.' && (i != 0 || str[i] != '-'))
            return false;
    }
    return true;
}

void BitcoinExchange::processInputFile(const std::string& input_file) {
    std::ifstream file(input_file.c_str());
    if (!file.is_open()) {
        throw FileError("Error: could not open input file.");
    }

    std::string line;
    bool hasValidData = false;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        try {
            // Skip empty lines or lines with only whitespace
            if (line.empty() || line.find_first_not_of(" \t\n\r") == std::string::npos)
                continue;

            // Handle comments - skip if line starts with # or is empty after removing comment
            size_t comment_pos = line.find('#');
            if (comment_pos != std::string::npos) {
                line = line.substr(0, comment_pos);
                if (line.find_first_not_of(" \t\n\r") == std::string::npos)
                    continue;
            }

            size_t separator = line.find(" | ");
            if (separator == std::string::npos) {
                std::cerr << "Error: input file bad format => " << line << std::endl;
                continue;
            }

            std::string date = line.substr(0, separator);
            std::string value_str = line.substr(separator + 3);
            
            // Trim whitespace from date and value
            while (!date.empty() && std::isspace(date[0]))
                date.erase(0, 1);
            while (!date.empty() && std::isspace(date[date.length() - 1]))
                date.erase(date.length() - 1);
            while (!value_str.empty() && std::isspace(value_str[0]))
                value_str.erase(0, 1);
            while (!value_str.empty() && std::isspace(value_str[value_str.length() - 1]))
                value_str.erase(value_str.length() - 1);
            
            if (!isValidDate(date)) {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }

            // First validate the number format
            if (!isValidNumber(value_str)) {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }

            // Then try to convert the value
            double value;
            char* end;
            errno = 0;  // Reset errno before conversion
            value = std::strtod(value_str.c_str(), &end);
            
            // Check for conversion errors or overflow
            if (*end != '\0' || errno == ERANGE) {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }

            // Then check value constraints
            if (value < 0) {
                std::cerr << "Error: not a positive number => " << line << std::endl;
                continue;
            }
            // According to subject, value must not be above 1000
            if (value > 1000) {
                std::cerr << "Error: too large a number => " << line << std::endl;
                continue;
            }

            double rate = getExchangeRate(date);
            hasValidData = true;
            
            // Determine input precision
            size_t decimal_pos = value_str.find('.');
            int precision = 2;  // default precision
            if (decimal_pos != std::string::npos) {
                precision = value_str.length() - decimal_pos - 1;
            }
            
            std::cout << std::fixed;
            std::cout.precision(precision);
            std::cout << date << " => " << value;
            std::cout.precision(2);  // reset to 2 decimal places for result
            std::cout << " = " << (value * rate) << std::endl;

        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    if (!hasValidData) {
        throw FileError("Error: no valid input found in file.");
    }
} 