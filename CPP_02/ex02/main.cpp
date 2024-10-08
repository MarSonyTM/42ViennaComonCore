/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:29:47 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/07 13:55:30 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

int     main( void ) {

    Fixed       a;   // Default constructor called to initialize a with fixedPointValue = 0
    Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) ); // Declares a constant Fixed object with the result of 5.05 * 2

    std::cout << a << std::endl;     // outputs the value of a
    std::cout << ++a << std::endl;   // Pre-increment - Increments the fixed-point value and returns a reference to the object
    std::cout << a << std::endl;     // outputs the value of a
    std::cout << a++ << std::endl;   // Post-increment - Increments the fixed-point value and returns a copy of the object
    std::cout << a << std::endl;     // outputs the value of a
    std::cout << b << std::endl;     // outputs the value of b

    std::cout << Fixed::max( a, b ) << std::endl;  // outputs the maximum value between a and b

    return (0);
}

/*
        This program creates two Fixed objects, a and b.
        The first Fixed object, a, is initialized with the default constructor,
        which sets the fixedPointValue to 0. The second Fixed object, b, is initialized with the result of multiplying two Fixed objects.
        The program then outputs the values of a and b, increments a using both pre-increment and post-increment operators, and outputs the values of a and b again.
        Finally, the program outputs the maximum value between a and b.


        Fixed-point representation is preferred in scenarios where performance,
        consistent presicion, lower memory usage, and deterministic behavior are critical.
        it is particularly useful 
*/