/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:28:58 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/07 13:38:17 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
                                      // Fixed-point number class definition
class Fixed {
private:
    int fixedPointValue;  // The raw fixed-point value
    static const int fractionalBits = 8;  // The number of fractional bits

public:
    Fixed();  // Default constructor
    Fixed(const int intValue);  // Constructor to convert int to fixed-point
    Fixed(const float floatValue);  // Constructor to convert float to fixed-point
    Fixed(const Fixed &copy);  // Copy constructor 
    Fixed &operator = (const Fixed &copy);  // Copy assignment operator
    ~Fixed();  // Destructor

    int getRawBits(void) const;  // Returns the raw value of the fixed point value
    void setRawBits(int const raw);  // Sets the raw value of the fixed point value

    float toFloat(void) const;  // Convert fixed-point to float
    int toInt(void) const;  // Convert fixed-point to int

    // Operator overloads                             // These operators are overloaded to compare fixed-point numbers
    bool operator > (const Fixed &other) const;
    bool operator < (const Fixed &other) const;
    bool operator >= (const Fixed &other) const;
    bool operator <= (const Fixed &other) const;
    bool operator == (const Fixed &other) const;
    bool operator != (const Fixed &other) const;

    // Arithmetic operators
    Fixed operator + (const Fixed &other) const;
    Fixed operator - (const Fixed &other) const;
    Fixed operator * (const Fixed &other) const;
    Fixed operator / (const Fixed &other) const;

    // Increment/Decrement Operators
    Fixed &operator ++();  // Pre-increment - Increments the fixed-point value and returns a reference to the object
    Fixed operator ++(int);  // Post-increment - Increments the fixed-point value and returns a copy of the object
    Fixed &operator --();  // Pre-decrement - Decrements the fixed-point value and returns a reference to the object
    Fixed operator --(int);  // Post-decrement - Decrements the fixed-point value and returns a copy of the object

    // Static functions                           // These functions are overloaded to compare fixed-point
    static Fixed &min(Fixed &a, Fixed &b);    // takes references to two fixed-point numbers and returns the minimum
    static const Fixed &min(const Fixed &a, const Fixed &b); // takes constant references to two fixed-point numbers and returns the minimum
    static Fixed &max(Fixed &a, Fixed &b);   // takes references to two fixed-point numbers and returns the maximum
    static const Fixed &max(const Fixed &a, const Fixed &b); // takes constant references to two fixed-point numbers and returns the maximum
};

// Overload the << operator to output the fixed-point number        // purpose of this function is to output the fixed-point number as a floating-point number
std::ostream &operator <<(std::ostream &out, const Fixed &fixed);

#endif
