/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:36:17 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/08 13:57:23 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
    // Creating ClapTrap objects
    ClapTrap claptrap0;                        // Default constructor
    ClapTrap claptrap1("Claptrap1");           // Parameterized constructor
    ClapTrap claptrap2(claptrap1);             // Copy constructor            
    claptrap0 = claptrap2;                     // Copy assignment operator                

    // Demonstrating attack, takeDamage, and beRepaired functions
    claptrap0.attack("target0");
    claptrap0.takeDamage(5);
    claptrap0.beRepaired(3);
    claptrap0.attack("target1");
    claptrap0.takeDamage(10);

    claptrap1.attack("target2");
    claptrap1.takeDamage(5);
    claptrap1.beRepaired(3);
    claptrap1.attack("target3");
    claptrap1.takeDamage(10);
    claptrap1.beRepaired(5);

    claptrap2.attack("target4");
    claptrap2.takeDamage(2);
    claptrap2.beRepaired(2);
    claptrap2.attack("target5");
    claptrap2.takeDamage(20);

    // Edge cases: No hit points or energy points left
    claptrap0.attack("target6");
    claptrap0.takeDamage(100);  // Ensure hit points go to 0
    claptrap0.beRepaired(10);  // Should not repair as hit points are 0

    // Creating ScavTrap objects
    ScavTrap scavtrap0;                        // Default constructor
    ScavTrap scavtrap1("Scavtrap1");     // Parameterized constructor
    ScavTrap scavtrap2(scavtrap1);            // Copy constructor            
    scavtrap0 = scavtrap2;                   // Copy assignment operator                

    // Demonstrating ScavTrap specific functions
    scavtrap0.attack("target7");
    scavtrap0.takeDamage(15);
    scavtrap0.beRepaired(10);
    scavtrap0.guardGate();

    scavtrap1.attack("target8");
    scavtrap1.takeDamage(20);
    scavtrap1.beRepaired(15);
    scavtrap1.guardGate();

    scavtrap2.attack("target9");
    scavtrap2.takeDamage(25);
    scavtrap2.beRepaired(20);
    scavtrap2.guardGate();

    return 0;
}