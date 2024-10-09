/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:16:01 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/09 22:54:19 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <string>

class ClapTrap {

private:
    std::string _name;    // Name of the ClapTrap
    int _hitpoints;      // Health points of the ClapTrap
    int _energyPoints;   // Energy points of the ClapTrap
    int _attackDamage;   // Damage points of the ClapTrap

public:                                                              
    ClapTrap();  // default constructor that initializes the obejct with default values
    ClapTrap(const std::string& name); // parameterized constructor that initializes the object with the given name and other default values
    ClapTrap(const ClapTrap& copy);    // copy constructor that initializes the object with the values of another existing object
    ClapTrap& operator = (const ClapTrap& copy); // copy assignment operator that assigns the values of another existing object to the current object
    ~ClapTrap(); // destructor that prints a message when the object is destroyed

    void attack(const std::string& target); // this function will simulate an attack on the target by decreasing energy points
    void takeDamage(unsigned int amount); // this function will simulate taking damage by decreasing hit points amount
    void beRepaired(unsigned int amount); // this function will simulate repairing the ClapTrap by increasing hit points amount
    void printState() const;
};

#endif