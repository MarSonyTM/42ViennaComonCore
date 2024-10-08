/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:19:44 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/08 13:04:09 by mafurnic         ###   ########.fr       */
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
    if (this != &other)
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
    if (_hitpoints <= 0 || _energyPoints <= 0)
    {
        std::cout << "ClapTrap " << _name << " has no hit points or energy points left!" << std::endl;
        return;
    }
    _energyPoints--; // decreasing point of energy
    std::cout << "ClapTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
}


// Function simulates taking damage by decreasing hit points and printing a message
void ClapTrap::takeDamage(unsigned int amount)
{
    _hitpoints -= amount; // decreasing point of hitpoints by amount
    if (_hitpoints < 0) _hitpoints = 0; // hitpoints cannot be negative
    std::cout << "ClapTrap " << _name << " takes " << amount << " points of damage! Hit points left: " << _hitpoints << std::endl;
}

// Function simulates being repaired by increasing hit points and printing a message
void ClapTrap::beRepaired(unsigned int amount)
{
    if (_hitpoints <= 0 || _energyPoints <= 0)
    {
        std::cout << "ClapTrap " << _name << " has no hit points or energy points left!" << std::endl;
        return;
    }
    _energyPoints--;
    _hitpoints += amount; // increasing point of hitpoints by amount
    std::cout << "ClapTrap " << _name << " is repaired by " << amount << " points! Hit points now: " << _hitpoints << std::endl;
}