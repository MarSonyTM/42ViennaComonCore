/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:18:30 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/10 12:29:09 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FlagTrap.hpp"
#include <iostream>
 
int main()
{
    FlagTrap flagtrap0;
    FlagTrap flagtrap1("FlagTrap");
    FlagTrap flagtrap2(flagtrap1);
    flagtrap0 = flagtrap2;    
    
    // Demonstrate working class with inherited methods
    std::cout << std::endl;
    flagtrap0.printState();
    flagtrap0.attack("Target");
    flagtrap0.takeDamage(10);
    flagtrap0.beRepaired(5);
    flagtrap0.printState();
    std::cout << std::endl;

    // Demonstrate new method
    flagtrap0.highFivesGuys();
    std::cout << std::endl;

    // Demonstrate error handling
    
                
    return (0);
}

/*
            In C++, the base class constructor is called before the derived class constructor.
            In C++, the base class destructor is called after the derived class destructor.
*/