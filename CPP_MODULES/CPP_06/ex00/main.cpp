/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:46:07 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/13 12:25:01 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int  main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <literal>" <<std::endl;
        return (1);
    }
    
    ScalarConverter::convert(argv[1]);
    return (0);
}

/*
    The main objective of this program is to convert a literal to the appropriate type.
    The program takes a single argument from the command line, which is the literal to convert.
    The program handles the following types: char, int, float, and double.
    The program also handles special literals: nan, nanf, +inf, -inf, +inff, -inff.
    Static Cast is used to convert the literal to the appropriate type.
    It is the best choice because:
                                1. type safety
                                2. it's explicit about what conversion is being done
                                3. it will generate a compile time error if the literal is not a valid number
                                4. it's more readable and easier to understand

Test cases to try:
./scalarconverter 0        // Integer
./scalarconverter 42       // Integer
./scalarconverter -42      // Negative integer
./scalarconverter 'a'      // Character
./scalarconverter '*'      // Non-alphanumeric character
./scalarconverter 42.0f    // Float
./scalarconverter 42.42f   // Float with decimals
./scalarconverter 42.0     // Double
./scalarconverter 42.42    // Double with decimals
./scalarconverter nan      // Special literal
./scalarconverter nanf     // Special literal float
./scalarconverter +inf     // Positive infinity
./scalarconverter -inf     // Negative infinity
./scalarconverter +inff    // Positive infinity float
./scalarconverter -inff    // Negative infinity float
./scalarconverter 2147483648  // Integer overflow
./scalarconverter abc      // Invalid input
*/