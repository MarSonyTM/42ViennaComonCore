/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:20:48 by marianfurni       #+#    #+#             */
/*   Updated: 2024/12/10 15:24:42 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

class BitcoinExchange {
private:
    std::map<std::string, double> _database;

    // Private helper methods
    bool isValidDate(const std::string& date) const;
    bool isValidValue(const double value) const;
    void loadDatabase(const std::string& filename);
    std::string findClosestDate(const std::string& date) const;

public:
    // Orthodox Canonical Form
    BitcoinExchange();
    BitcoinExchange(const std::string& database_file);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    // Main functionality
    void processInputFile(const std::string& input_file);
    double getExchangeRate(const std::string& date) const;

    // Exception classes
    class FileError : public std::runtime_error {
        public:
            explicit FileError(const std::string& msg) : std::runtime_error(msg) {}
    };

    class DateError : public std::runtime_error {
        public:
            explicit DateError(const std::string& msg) : std::runtime_error(msg) {}
    };

    class ValueError : public std::runtime_error {
        public:
            explicit ValueError(const std::string& msg) : std::runtime_error(msg) {}
    };
};
