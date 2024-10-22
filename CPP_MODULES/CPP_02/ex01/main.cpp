/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:02:48 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/07 15:10:45 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

int		main( void )
{

Fixed 		a;                              // Default constructor called to initialize a                      
Fixed const b( 10 );              // Int constructor called to initialize b
Fixed const c( 42.42f );       // Float constructor called to initialize c
Fixed const d( b );                       // Copy constructor called to initialize d from b

a = Fixed( 1234.4321f );       // Float constructor called to initialize a, then copy assignment operator called to assign a to a new Fixed object

std::cout << "a is " << a << std::endl;
std::cout << "b is " << b << std::endl;     // Overloaded << operator called to display the Fixed object
std::cout << "c is " << c << std::endl;
std::cout << "d is " << d << std::endl;

std::cout << "a is " << a.toInt() << " as integer" << std::endl;
std::cout << "b is " << b.toInt() << " as integer" << std::endl;
std::cout << "c is " << c.toInt() << " as integer" << std::endl;
std::cout << "d is " << d.toInt() << " as integer" << std::endl;

return (0);
}

