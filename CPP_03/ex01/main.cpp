/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:18:30 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/10 11:20:48 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>
 
int main()
{
    // Creating ClapTrap objects
    ClapTrap claptrap0;                        // Default constructor
    ClapTrap claptrap1("Wally");     // Parameterized constructor
    ClapTrap claptrap2(claptrap1);            // Copy constructor            
    claptrap0 = claptrap2;                    // Copy assignment operator                

    std::cout << std::endl;
    
    // // Demonstrating attack, takeDamage, and beRepaired functions
    
    claptrap0.printState();
    claptrap0.attack("target0");  // this will decrease energy points
    claptrap0.takeDamage(5);     // this will decrease hit points
    claptrap0.beRepaired(3);   // this will increase hit points and decrease energy points
    claptrap0.attack("target1");  
    claptrap0.takeDamage(10);
    std::cout << std::endl;

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

    // Demonstrating guardGate function
    scavtrap0.guardGate();
    std::cout << std::endl;

    // Demostrating no action when hit points are 0
    ScavTrap scavtrap3("Scavtrap3");
    scavtrap3.printState();
    scavtrap3.takeDamage(101); // this will decrease hit points to 0
    scavtrap3.attack("target2"); // this will print a message that the object has no hit points

    // Demostarting no action when energy points are 0
    ScavTrap scavtrap4("Scavtrap4");
    scavtrap4.printState();
    for(int i = 0; i < 50; i++)
        scavtrap4.attack("target3"); // this will decrease energy points to 0
    scavtrap4.attack("target4"); // this will print a message that the object has no energy points

    return (0);
}

/*
            In C++, the base class constructor is called before the derived class constructor.
            In C++, the base class destructor is called after the derived class destructor.
*/