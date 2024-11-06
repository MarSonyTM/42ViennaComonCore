/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:46:07 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/06 13:36:35 by marianfurni      ###   ########.fr       */
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
./convert 0        // Integer
./convert 42       // Integer
./convert -42      // Negative integer
./convert 'a'      // Character
./convert '*'      // Non-alphanumeric character
./convert 42.0f    // Float
./convert 42.42f   // Float with decimals
./convert 42.0     // Double
./convert 42.42    // Double with decimals
./convert nan      // Special literal
./convert nanf     // Special literal float
./convert +inf     // Positive infinity
./convert -inf     // Negative infinity
./convert +inff    // Positive infinity float
./convert -inff    // Negative infinity float
./convert 2147483648  // Integer overflow
./convert abc      // Invalid input
*/