/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlagTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:34:37 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/10 12:23:29 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FlagTrap.hpp"
#include "ClapTrap.hpp"
#include <iostream>

FlagTrap::FlagTrap() : ClapTrap()
{
    _hitPoints = 100;
    _energyPoints = 100;
    _attackDamage = 30;
    std::cout << "FlagTrap default constructor called" << std::endl;
}

FlagTrap::FlagTrap(const std::string& name) : ClapTrap(name)
{
    _hitPoints = 100;
    _energyPoints = 100;
    _attackDamage = 30;
    std::cout << "FlagTrap name constructor called" << std::endl;
}

FlagTrap::FlagTrap(const FlagTrap& other) : ClapTrap(other)
{
    *this = other;
    std::cout << "FlagTrap copy constructor called" << std::endl;
}

FlagTrap& FlagTrap::operator = (const FlagTrap& other)
{
    if (this != &other)
    {
        ClapTrap::operator=(other); // Calls the base class assignment operator
        _name = other._name;
        _hitPoints = other._hitPoints;
        _energyPoints = other._energyPoints;
        _attackDamage = other._attackDamage;
    }
    std::cout << "FlagTrap assignation operator called" << std::endl;
    return (*this);
}

FlagTrap::~FlagTrap()
{
    std::cout << "FlagTrap destructor called" << std::endl;
}

void FlagTrap::highFivesGuys(void)
{
    std::cout << "FlagTrap " << _name << " is requesting a high five!" << std::endl;
}