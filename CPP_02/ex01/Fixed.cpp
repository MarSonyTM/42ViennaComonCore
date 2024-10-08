/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:53:21 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/07 14:01:24 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <cmath>

// Default constructor
Fixed::Fixed() : fixedPointValue(0)
{
    std::cout << "Default constructor called" << std::endl;
}

// Constructor to convert an integer to a fixed point value
Fixed::Fixed(const int intValue)
{
    std::cout << "Int constructor called" << std::endl;
    fixedPointValue = intValue << fractionalBits; // Shift the integer to the left by the number of fractional bits
}

// Constructor to convert a float to a fixed point value
Fixed::Fixed(const float floatValue)
{
    std::cout << "Float constructor called" << std::endl;       // bitshift the float value to the left by the number of fractional bits
    fixedPointValue = roundf(floatValue * (1 << fractionalBits)); // Multiply the float by 2^fractionalBits and round the result
}

// Copy constructor , initializes a new Fixed object from an existing one
Fixed::Fixed(const Fixed &copy)
{
    std::cout << "Copy constructor called" << std::endl;
    this->fixedPointValue = copy.getRawBits();   
}

// Copy assignment operator   , assigns the values from one Fixed object to existing Fixed object.
Fixed &Fixed::operator = (const Fixed &copy)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &copy)
        this->fixedPointValue = copy.getRawBits();
    return (*this);
}

// Destructor
Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

// Getter for raw bits
int Fixed::getRawBits(void) const
{
    return (this->fixedPointValue);
}

// Setter for raw bits
void Fixed::setRawBits(int const raw)
{
    this->fixedPointValue = raw;
}

// Convert the fixed point value to a float
float Fixed::toFloat(void) const
{
    return (static_cast<float>(this->fixedPointValue) / (1 << fractionalBits)); // Divide the fixed point value by 2^fractionalBits
}

// Convert the fixed point value to an integer
int Fixed::toInt(void) const
{
    return (this->fixedPointValue >> fractionalBits); // Shift the fixed point value to the right by the number of fractional bits
}

// Overload of << operator to display the fixed point value
std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
    out << fixed.toFloat();
    return (out); // Return the ostream object
}
