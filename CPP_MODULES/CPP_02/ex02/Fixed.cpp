/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:28:18 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/07 15:27:48 by mafurnic         ###   ########.fr       */
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

// Constructor to convert an integer to fixed-point
Fixed::Fixed(const int intValue) 
{
    std::cout << "Int constructor called" << std::endl;
    fixedPointValue = intValue << fractionalBits;  // Shift left by fractional bits
}

// Constructor to convert a float to fixed-point
Fixed::Fixed(const float floatValue)
 {
    std::cout << "Float constructor called" << std::endl;
    fixedPointValue = roundf(floatValue * (1 << fractionalBits));  // Multiply by 2^fractionalBits
}

// Copy constructor
Fixed::Fixed(const Fixed &copy) 
{
    std::cout << "Copy constructor called" << std::endl;
    this->fixedPointValue = copy.getRawBits();
}

// Copy assignment operator
Fixed &Fixed::operator=(const Fixed &copy)
 {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &copy) 
    {
        this->fixedPointValue = copy.getRawBits();
    }
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

// Convert fixed-point to float
float Fixed::toFloat(void) const    
{
    return (static_cast<float>(fixedPointValue) / (1 << fractionalBits));  // Divide by 2^fractionalBits
}

// Convert fixed-point to int
int Fixed::toInt(void) const 
{
    return (fixedPointValue >> fractionalBits);  // Shift right by fractional bits
}

// Overload comparison operators
bool Fixed::operator>(const Fixed &other) const
{
    return (this->fixedPointValue > other.fixedPointValue);
}

bool Fixed::operator<(const Fixed &other) const 
{
    return (this->fixedPointValue < other.fixedPointValue);
}

bool Fixed::operator>=(const Fixed &other) const 
{
    return (this->fixedPointValue >= other.fixedPointValue);
}

bool Fixed::operator<=(const Fixed &other) const 
{
    return (this->fixedPointValue <= other.fixedPointValue);
}

bool Fixed::operator==(const Fixed &other) const 
{
    return (this->fixedPointValue == other.fixedPointValue);
}

bool Fixed::operator!=(const Fixed &other) const 
{
    return (this->fixedPointValue != other.fixedPointValue);
}

// Overload arithmetic operators
Fixed Fixed::operator+(const Fixed &other) const 
{
    Fixed result;
    result.setRawBits(this->fixedPointValue + other.getRawBits());
    return (result);
}

Fixed Fixed::operator-(const Fixed &other) const 
{
    Fixed result;
    result.setRawBits(this->fixedPointValue - other.getRawBits());
    return (result);
}

Fixed Fixed::operator*(const Fixed &other) const 
{
    Fixed result;
    result.setRawBits((this->fixedPointValue * other.getRawBits()) >> fractionalBits);  // Adjust for fixed-point multiplication
    return (result);
}

Fixed Fixed::operator/(const Fixed &other) const 
{
    if (other.getRawBits() == 0) 
    {
        std::cerr << "Error: Division by zero!" << std::endl;
        return (Fixed());  // Return a default Fixed object if division by zero
    }
    Fixed result;
    result.setRawBits((this->fixedPointValue << fractionalBits) / other.getRawBits());  // Adjust for fixed-point division
    return (result);
}

// Increment operators
Fixed &Fixed::operator++() 
{  // Pre-increment
    this->fixedPointValue++;
    return (*this);
}

Fixed Fixed::operator++(int) 
{  // Post-increment
    Fixed temp = *this;  // Save current state
    ++(*this);  // Pre-increment
    return (temp);  // Return old state
}

Fixed &Fixed::operator--() 
{  // Pre-decrement
    this->fixedPointValue--;
    return (*this);
}

Fixed Fixed::operator--(int) 
{  // Post-decrement
    Fixed temp = *this;  // Save current state
    --(*this);  // Pre-decrement
    return temp;  // Return old state
}

// Static member functions for min and max
Fixed &Fixed::min(Fixed &a, Fixed &b) 
{
    return ((a < b) ? a : b);
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) 
{
    return ((a < b) ? a : b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b) 
{
    return ((a > b) ? a : b);
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) 
{
    return ((a > b) ? a : b);
}

// Overload the << operator to output fixed-point numbers
std::ostream &operator<<(std::ostream &out, const Fixed &fixed) 
{
    out << fixed.toFloat();
    return (out);
}
