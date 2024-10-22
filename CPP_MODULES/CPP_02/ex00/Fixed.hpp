/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:14:36 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/07 12:01:21 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP
                                        // this file declares the Fixed class and its members variables and functions
class Fixed {

private:
    int fixedPointValue; // The raw fixed-point value (integer)
    static const int fractionalBits = 8; // A static constant integer that represents the number of fractional bits

public:
    Fixed(); // Default constructor that itializes the fixed point value to 0
    Fixed(const Fixed &copy); // Copy constructor that creates a new object as a copy of an existing object
    Fixed &operator=(const Fixed &copy); // Copy assignment operator that assigns the values from one object to another existing object
    ~Fixed(); // Destructor that cleans up  resources when the object is destroyed

    int getRawBits(void) const; // Returns the raw value of the fixed point value (Getter)
    void setRawBits(int const raw); // Sets the raw value of the fixed point value (Setter)
};

#endif