/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:10:37 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/05 12:50:32 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string &literal) {
    char charValue;
    int intValue;
    float floatValue;
    double doubleValue;

    // Detect the type and convert
    try {
        // Try to convert to char
        if (literal.length() == 1 && !isdigit(literal[0])) {
            charValue = literal[0];
            intValue = static_cast<int>(charValue);
            floatValue = static_cast<float>(charValue);
            doubleValue = static_cast<double>(charValue);
        } else {
            // Try to convert to int
            char *end;
            long tempInt = std::strtol(literal.c_str(), &end, 10);
            if (*end == '\0') {
                intValue = static_cast<int>(tempInt);
                charValue = static_cast<char>(intValue);
                floatValue = static_cast<float>(intValue);
                doubleValue = static_cast<double>(intValue);
            } else {
                // Try to convert to float
                float tempFloat = std::strtof(literal.c_str(), &end);
                if (*end == 'f' && *(end + 1) == '\0') {
                    floatValue = tempFloat;
                    doubleValue = static_cast<double>(floatValue);
                    intValue = static_cast<int>(floatValue);
                    charValue = static_cast<char>(floatValue);
                } else {
                    // Try to convert to double
                    double tempDouble = std::strtod(literal.c_str(), &end);
                    if (*end == '\0') {
                        doubleValue = tempDouble;
                        floatValue = static_cast<float>(doubleValue);
                        intValue = static_cast<int>(doubleValue);
                        charValue = static_cast<char>(doubleValue);
                    } else {
                        throw std::invalid_argument("Invalid literal");
                    }
                }
            }
        }
    } catch (const std::exception &e) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    // Display results
    if (isprint(charValue))
        std::cout << "char: '" << charValue << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;

    std::cout << "int: " << intValue << std::endl;

    if (std::isnan(floatValue) || std::isinf(floatValue))
        std::cout << "float: " << floatValue << "f" << std::endl;
    else
        std::cout << "float: " << floatValue << "f" << std::endl;

    if (std::isnan(doubleValue) || std::isinf(doubleValue))
        std::cout << "double: " << doubleValue << std::endl;
    else
        std::cout << "double: " << doubleValue << std::endl;
}