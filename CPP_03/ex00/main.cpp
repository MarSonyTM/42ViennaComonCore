/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:36:17 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/09 23:07:52 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

int main()
{
    ClapTrap claptrap0("ClapTrap0");
    ClapTrap claptrap1("ClapTrap1");

    ClapTrap claptrap2(claptrap1);  // Copy constructor
    claptrap0 = claptrap2;          // Copy assignment operator

    std::cout << std::endl;

    // Demonstrating attack, takeDamage, and beRepaired functions
    std::cout << "Testing ClapTrap0:" << std::endl;
    claptrap0.printState();
    claptrap0.attack("target0");  // energy points--
    claptrap0.takeDamage(5);      // hit points++
    claptrap0.beRepaired(3);      // hit points++ energy points--
    claptrap0.attack("target1");
    claptrap0.takeDamage(10);
    claptrap0.attack("target1");

    std::cout << std::endl;

    std::cout << "Testing ClapTrap1:" << std::endl;
    claptrap1.printState();
    claptrap1.attack("target2");
    claptrap1.takeDamage(5);
    claptrap1.beRepaired(3);
    claptrap1.attack("target3");
    claptrap1.takeDamage(10);
    claptrap1.beRepaired(5);

    std::cout << std::endl;

    std::cout << "Testing ClapTrap2:" << std::endl;
    claptrap2.printState();
    claptrap2.attack("target4");
    claptrap2.takeDamage(7);
    claptrap2.beRepaired(4);
    claptrap2.attack("target5");
    claptrap2.takeDamage(10);
    claptrap2.beRepaired(6);

    std::cout << std::endl;

    // Edge cases
    std::cout << "Testing edge cases:" << std::endl;
    ClapTrap claptrap3("ClapTrap3");
    claptrap3.takeDamage(10);  // Reduce hit points to 0
    claptrap3.attack("target6");  // Should not be able to attack
    claptrap3.beRepaired(5);  // Should not be able to repair

    ClapTrap claptrap4("ClapTrap4");
    for (int i = 0; i < 11; ++i) {
        claptrap4.attack("target7");  // Reduce energy points to 0
    }
    claptrap4.beRepaired(5);  // Should not be able to repair

    return (0);
}