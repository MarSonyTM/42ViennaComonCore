/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:36:17 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/08 13:15:20 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

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
    claptrap0.takeDamage(100); // Ensure hit points go to 0
    claptrap0.beRepaired(10);  // Should not repair as hit points are 0

    return (0);
}