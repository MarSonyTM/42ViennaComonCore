/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:21:55 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/04 15:22:00 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
private:
    int fixedPointValue;  // The raw fixed-point value
    static const int fractionalBits = 8;  // The number of fractional bits

public:
    Fixed();  // Default constructor
    Fixed(const int intValue);  // Constructor to convert int to fixed-point
    Fixed(const float floatValue);  // Constructor to convert float to fixed-point
    Fixed(const Fixed &copy);  // Copy constructor
    Fixed &operator=(const Fixed &copy);  // Copy assignment operator
    ~Fixed();  // Destructor

    int getRawBits(void) const;  // Returns the raw value of the fixed point value
    void setRawBits(int const raw);  // Sets the raw value of the fixed point value

    float toFloat(void) const;  // Convert fixed-point to float
    int toInt(void) const;  // Convert fixed-point to int

    // Operator overloads
    bool operator>(const Fixed &other) const;
    bool operator<(const Fixed &other) const;
    bool operator>=(const Fixed &other) const;
    bool operator<=(const Fixed &other) const;
    bool operator==(const Fixed &other) const;
    bool operator!=(const Fixed &other) const;

    Fixed operator+(const Fixed &other) const;
    Fixed operator-(const Fixed &other) const;
    Fixed operator*(const Fixed &other) const;
    Fixed operator/(const Fixed &other) const;

    // Increment/Decrement Operators
    Fixed &operator++();  // Pre-increment
    Fixed operator++(int);  // Post-increment
    Fixed &operator--();  // Pre-decrement
    Fixed operator--(int);  // Post-decrement

    // Static functions
    static Fixed &min(Fixed &a, Fixed &b);
    static const Fixed &min(const Fixed &a, const Fixed &b);
    static Fixed &max(Fixed &a, Fixed &b);
    static const Fixed &max(const Fixed &a, const Fixed &b);
};

// Overload the << operator to output the fixed-point number
std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif
