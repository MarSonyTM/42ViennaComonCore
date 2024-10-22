/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:36:17 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/09 23:02:33 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

int main()
{
    // Creating ClapTrap objects
    ClapTrap claptrap0;                        // Default constructor
    ClapTrap claptrap1("Wally");     // Parameterized constructor
    ClapTrap claptrap2(claptrap1);            // Copy constructor            
    claptrap0 = claptrap2;                    // Copy assignment operator                

    std::cout << std::endl;
    
    // Demonstrating attack, takeDamage, and beRepaired functions
    
    claptrap0.printState();
    claptrap0.attack("target0");  // this will decrease energy points
    claptrap0.takeDamage(5);     // this will decrease hit points
    claptrap0.beRepaired(3);   // this will increase hit points and decrease energy points
    claptrap0.attack("target1");  
    claptrap0.takeDamage(10);
    claptrap0.attack("target1"); 
    
    std::cout << std::endl;

    // claptrap1.printState();
    // claptrap1.attack("target2");
    // claptrap1.takeDamage(5);
    // claptrap1.beRepaired(3);
    // claptrap1.attack("target3");
    // claptrap1.takeDamage(10);
    // claptrap1.beRepaired(5);
    // std::cout << std::endl;

    // claptrap2.printState();
    // claptrap2.attack("target4");
    // claptrap2.takeDamage(2);
    // claptrap2.beRepaired(2);
    // claptrap2.attack("target5");
    // claptrap2.takeDamage(20);
    // std::cout << std::endl;

    // //cases: No hit points or energy points left
    // std::cout << "cases where No hit points or energy points left" << std::endl;
    // claptrap2.printState();
    // claptrap0.attack("target6");
    // claptrap0.takeDamage(100); // Ensure hit points go to 0
    // claptrap0.attack("target7");  // Should not attack as energy points are 0
    // claptrap0.takeDamage(100);
    // claptrap0.beRepaired(10);  // Should not repair as hit points are 0
    // std::cout << std::endl;

    return (0);
}