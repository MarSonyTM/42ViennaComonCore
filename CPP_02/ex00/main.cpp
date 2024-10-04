/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:06:38 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/04 12:08:16 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

int main()
{
    Fixed a;
    Fixed b(a);
    Fixed c;
    c = b;

    std::cout << "a:" << a.getRawBits() << std::endl;
    std::cout << "b:" << b.getRawBits() << std::endl;
    std::cout << "c:" << c.getRawBits() << std::endl;

    return (0);
}