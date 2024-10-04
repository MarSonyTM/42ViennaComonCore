/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:20:14 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/04 12:08:58 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

// Default constructor
Fixed::Fixed() : fixedPointValue(0)     // Initialize the fixedPointValue to 0
{
    std::cout << "Default constructor called" << std::endl;
}

// Copy constructor 
Fixed::Fixed(const Fixed &copy)          // takes a constant reference to another Fixed object and copies its raw value
{
    std::cout << "Copy constructor called" << std::endl;
    this->fixedPointValue = copy.getRawBits();
}

// Copy assignment operator
Fixed &Fixed::operator = (const Fixed &copy)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &copy) // Prevet self-assignment
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
    std::cout << "getRawBits member function called" << std::endl;
    return (this->fixedPointValue);
}

// Setter for raw bits
void Fixed::setRawBits(int const raw)
{
    this->fixedPointValue = raw;
}