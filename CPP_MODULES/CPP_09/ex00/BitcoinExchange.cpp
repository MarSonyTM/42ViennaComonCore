/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:23:17 by marianfurni       #+#    #+#             */
/*   Updated: 2024/12/16 17:04:33 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

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
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    try {
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));

        if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31)
            return false;

        // Basic month length validation
        if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day > 30) return false;
        } else if (month == 2) {
            bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (day > (isLeap ? 29 : 28)) return false;
        }

        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool BitcoinExchange::isValidValue(const double value) const {
    return value >= 0 && value <= 1000;
}

void BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw FileError("Could not open database file: " + filename);
    }

    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date;
        double value;
        
        if (std::getline(iss, date, ',') && iss >> value) {
            if (isValidDate(date)) {
                _database[date] = value;
            }
        }
    }
    
    if (_database.empty()) {
        throw FileError("No valid data in database file");
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
    return _database.at(closest_date);
}

void BitcoinExchange::processInputFile(const std::string& input_file) {
    std::ifstream file(input_file.c_str());
    if (!file.is_open()) {
        throw FileError("Error: could not open file.");
    }

    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        try {
            // Skip empty lines, comments, or lines with only whitespace
            if (line.empty() || line[0] == '#' || line.find_first_not_of(" \t\n\r") == std::string::npos)
                continue;

            size_t separator = line.find(" | ");
            if (separator == std::string::npos) {
                std::cout << "Error: bad input => " << line << std::endl;
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
                std::cout << "Error: invalid date format or out of range => " << date << std::endl;
                continue;
            }

            double value;
            std::istringstream iss(value_str);
            if (!(iss >> value) || !iss.eof()) {
                std::cout << "Error: invalid value." << std::endl;
                continue;
            }

            if (value < 0) {
                std::cout << "Error: not a positive number." << std::endl;
                continue;
            }
            if (value > 1000) {
                std::cout << "Error: too large a number." << std::endl;
                continue;
            }

            double rate = getExchangeRate(date);
            std::cout << date << " => " << value << " = " << (value * rate) << std::endl;

        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
} 