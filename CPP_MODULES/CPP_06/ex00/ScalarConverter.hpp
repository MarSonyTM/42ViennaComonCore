/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:48:46 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/06 14:05:57 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream> // For input and output operations
#include <string> // For string handling
#include <limits> // For limits operations
#include <cmath> // For mathematical operations (isnan, isinf)
#include <cstdlib> // For string to number conversion
#include <climits> // For INT_MAX and INT_MIN
#include <iomanip> // For setprecision

class ScalarConverter {
    private:
    // Private constructors and destructor make the class non-instantiable
        ScalarConverter();
        ScalarConverter(const ScalarConverter &);
        ScalarConverter &operator=(const ScalarConverter &);
        ~ScalarConverter();

    public:
        // Public static method to convert the literal to the appropriate type
        static void convert(const std::string &literal);
};  

// This Class only provides a static method to convert a literal to the appropriate type.
