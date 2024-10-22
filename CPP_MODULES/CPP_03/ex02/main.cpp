/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:18:30 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/10 12:43:54 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <iostream>
 
int main()
{
    FragTrap fragtrap0;
    FragTrap fragtrap1("FragTrap");
    FragTrap fragtrap2(fragtrap1);
    fragtrap0 = fragtrap2;    
    
    // Demonstrate working class with inherited methods
    std::cout << std::endl;
    fragtrap0.printState();
    fragtrap0.attack("Target");
    fragtrap0.takeDamage(10);
    fragtrap0.beRepaired(5);
    fragtrap0.printState();
    std::cout << std::endl;

    // Demonstrate new method
    fragtrap0.highFivesGuys();
    std::cout << std::endl;

    // Demonstrate error handling
    
                
    return (0);
}

/*
            In C++, the base class constructor is called before the derived class constructor.
            In C++, the base class destructor is called after the derived class destructor.
*/