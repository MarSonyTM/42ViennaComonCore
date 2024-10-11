/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:18:30 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/11 09:56:57 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include <iostream>
 
int main()
{
    DiamondTrap diamondtrap0; // Calls the default constructor
    DiamondTrap diamondtrap1("DiamondTrap"); // Calls the parameterized constructor
    DiamondTrap diamondtrap2(diamondtrap1); // Calls the copy constructor
    diamondtrap0 = diamondtrap2; // Calls the copy assignment operator

    // // Demonstrate working class with inherited methods
    std::cout << std::endl;
    diamondtrap1.printState();
    diamondtrap1.attack("target");
    diamondtrap1.whoAmI();
    std::cout << std::endl;
     
    return (0);
}

/*
            In C++, the base class constructor is called before the derived class constructor.
            In C++, the base class destructor is called after the derived class destructor.
*/