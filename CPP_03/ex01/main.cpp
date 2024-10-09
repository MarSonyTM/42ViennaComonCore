/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:18:30 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/09 16:33:33 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>
 
int main()
{
    // // Creating ClapTrap objects
    // ClapTrap claptrap0;                        // Default constructor
    // ClapTrap claptrap1("Wally");     // Parameterized constructor
    // ClapTrap claptrap2(claptrap1);            // Copy constructor            
    // claptrap0 = claptrap2;                    // Copy assignment operator                

    // std::cout << std::endl;
    
    // // Demonstrating attack, takeDamage, and beRepaired functions
    
    // claptrap0.printState();
    // claptrap0.attack("target0");  // this will decrease energy points
    // claptrap0.takeDamage(5);     // this will decrease hit points
    // claptrap0.beRepaired(3);   // this will increase hit points and decrease energy points
    // claptrap0.attack("target1");  
    // claptrap0.takeDamage(10);
    // std::cout << std::endl;

    // Creating ScavTrap objects
    
    ScavTrap scavtrap0;                        // Default constructor
    ScavTrap scavtrap1("Scav");     // Parameterized constructor
    ScavTrap scavtrap2(scavtrap1);            // Copy constructor
    scavtrap0 = scavtrap2;                    // Copy assignment operator

    std::cout << std::endl;

    // Demonstrating attack, takeDamage, and beRepaired functions

    scavtrap0.printState();
    scavtrap0.attack("target0");  // this will decrease energy points
    scavtrap0.takeDamage(5);     // this will decrease hit points
    scavtrap0.beRepaired(3);   // this will increase hit points and decrease energy points
    scavtrap0.attack("target1");
    scavtrap0.takeDamage(10);
    std::cout << std::endl;

    return (0);
}
