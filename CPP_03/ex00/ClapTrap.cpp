/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:19:44 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/09 16:35:08 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>


ClapTrap::ClapTrap() : _name("Default"), _hitpoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap " << _name << " has been created (default constructor)." << std::endl;
}

ClapTrap::ClapTrap(const std::string& name) : _name(name), _hitpoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap " << _name << " has been created (parameterized constructor)." << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other) : _name(other._name), _hitpoints(other._hitpoints), _energyPoints(other._energyPoints), _attackDamage(other._attackDamage)
{
    std::cout << "ClapTrap " << _name << " has been copied (copy constructor)." << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
    if (this != &other)  // Avoid copying the object into itself
    {
        _name = other._name;
        _hitpoints = other._hitpoints;
        _energyPoints = other._energyPoints;
        _attackDamage = other._attackDamage;
    }
    std::cout << "ClapTrap " << _name << " has been assigned (copy assignment operator)." << std::endl;
    return (*this);
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap " << _name << " has been destroyed." << std::endl;
}

// Function simulates an attack on target by decreasing energy points and printing a message
void ClapTrap::attack(const std::string& target)        
{
    
    if (_energyPoints <= 0)
    {
        std::cout << "ClapTrap" << _name << " is trying to hit but has no energy points left , can't attack !" << std::endl;
        return;
    }
    if (_hitpoints <= 0)
    {
        std::cout << "ClapTrap" << _name << " is trying to hit  but has no hit points, can't be hit!" << std::endl;
        return;
    }
    _energyPoints--; // decreasing point of energy
    std::cout << "ClapTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " Attack Damage !" << "  Energy Points--" << std::endl;
    printState();
}

// Function simulates taking damage by decreasing hit points and printing a message
void ClapTrap::takeDamage(unsigned int amount)
{
    _hitpoints -= amount; // decreasing point of hitpoints by amount
    if (_hitpoints < 0)
         std::cout << "ClapTrap " << _name << " is getting hit with  " << amount << " Hit Points, but cannot take any more damage ! No more Hit points left" << std::endl;
    else
        std::cout << "ClapTrap " << _name << " takes Damage -" << amount << " to Hit Points" << std::endl;
    printState();
}

// Function simulates being repaired by increasing hit points and printing a message
void ClapTrap::beRepaired(unsigned int amount)
{
    if (_hitpoints <= 0)
    {
        std::cout << "ClapTrap " << _name << " trying to be repaired but has no Hit Points!" << std::endl;
        return;
    }
    if (_energyPoints <= 0)
    {
        std::cout << "ClapTrap " << _name << "trying to be repaired but has no Energy Points left!" << std::endl;
        return;
    }
    _energyPoints--;
    _hitpoints += amount; // increasing point of hitpoints by amount
    std::cout << "ClapTrap " << _name << " is repaired by Hit Points + "<< amount << "  Energy Points--" <<std::endl;
    printState();
}

// Function prints the state of the ClapTrap
void ClapTrap::printState() const {
    std::cout << "ClapTrap " << _name << "    Hit Points: " << _hitpoints
              << "    Energy Points: " << _energyPoints
              << "    Attack Damage: " << _attackDamage << std::endl;
}