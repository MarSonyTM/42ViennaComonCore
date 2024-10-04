/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:14:36 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/04 11:17:40 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

class Fixed {

private:
    int fixedPointValue; // The raw fixed-point value (integer)
    static const int fractionalBits = 8; // The number of fractional bits

public:
    Fixed(); // Default constructor
    Fixed(const Fixed &copy); // Copy constructor
    Fixed &operator=(const Fixed &copy); // Copy assignment operator
    ~Fixed(); // Destructor

    int getRawBits(void) const; // Returns the raw value of the fixed point value (Getter)
    void setRawBits(int const raw); // Sets the raw value of the fixed point value (Setter)
};

#endif