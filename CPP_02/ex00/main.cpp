/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:06:38 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/07 12:17:49 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

int main()
{
    Fixed a; // Default constructor called that initializes the fixed point value to 0
    Fixed b(a); // Copy constructor called that creates a new object as a copy of an existing object
    Fixed c; // Default constructor called that initializes the fixed point value to 0
    c = b; // Copy assignment operator called that assigns the values from one object to another existing object

    std::cout << "a:" << a.getRawBits() << std::endl; // Print the raw value of each object
    std::cout << "b:" << b.getRawBits() << std::endl; // Print the raw value of each object  ->   by using the getter we created
    std::cout << "c:" << c.getRawBits() << std::endl; // Print the raw value of each object

    return (0);
}

















/*
        Fixed Point Numbers are a way to represent numbers with a fixed number of digits after the decimal point.
        In this exercise, i had  to implement a class that represents a fixed point number with 8 bits after the decimal point.
        The class will have the following members:
            - An integer that stores the fixed point value
            - A static constant integer that represents the number of fractional bits
        The class will have the following member functions:
            - A default constructor that initializes the fixed point value to 0
            - A copy constructor that creates a new object as a copy of an existing object
            - A copy assignment operator that assigns the values from one object to another existing object
            - A destructor that cleans up resources when the object is destroyed
            - A getter that returns the raw value of the fixed point value
            - A setter that sets the raw value of the fixed point value
        In the main function,i will create three Fixed objects, a, b, and c. 
        Program will then print the raw value of each object.


        
        - Integers: Fixed precision, no fractional part, limited range, fast arithmetic, less memory.
        - Floating-Point Numbers: Variable precision, fractional part, wide range, complex arithmetic, more memory.
        - Fixed-Point Numbers: Fixed precision, fractional part, limited range, intermediate performance, intermediate memory usage.

        Understanding these differences helps in choosing the right type
        of number representation for specific applications, balancing the trade-offs between precision,
        range, performance, and memory usage.
*/