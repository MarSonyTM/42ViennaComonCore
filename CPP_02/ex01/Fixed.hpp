/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:49:14 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/07 12:29:59 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>  

class Fixed {

private:
    int fixedPointValue; // The raw fixed point value
    static const int fractionalBits = 8; // The number of fractional bits

public:
    Fixed(); // Default constructor
    Fixed(const int intValue); // Constructor that takes an integer value and converts it to fixed point
    Fixed(const float floatValue); // Constructor that takes a float value and converts it to fixed point
    Fixed(const Fixed &copy); // Copy constructor that creates a new Fixed object from an existing one
    Fixed &operator = (const Fixed &copy); // Copy assignment operator that assigns a new Fixed object to an existing one
    ~Fixed(); // Destructor

    int getRawBits(void) const; // Returns the raw value of the fixed point value (Getter)
    void setRawBits(int const raw); // Sets the raw value of the fixed point value (Setter)

    float toFloat(void) const; // Converts the fixed point value to a floating point value
    int toInt(void) const; // Converts the fixed point value to an integer value
};

std::ostream &operator<<(std::ostream &out, const Fixed &fixed); // Overload of << operator to display Fixed object

#endif