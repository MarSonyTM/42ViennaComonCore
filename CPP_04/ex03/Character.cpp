/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:17:14 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/18 11:24:32 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "AMateria.hpp" // Include the full definition of AMateria

Character::Character(std::string const &name) : name(name)
{
    for (int i = 0; i < 4; ++i)
    {
        inventory[i] = NULL; // Use NULL instead of nullptr
    }
}

Character::Character(const Character &other) : name(other.name)
{
    for (int i = 0; i < 4; ++i)
    {
        if (other.inventory[i])
        {
            inventory[i] = other.inventory[i]->clone();
        } 
        else
        {
            inventory[i] = NULL; // Use NULL instead of nullptr
        }
    }
}

Character& Character::operator=(const Character &other)
{
    if (this != &other)
    {
        name = other.name;
        for (int i = 0; i < 4; ++i)
        {
            if (inventory[i])
            {
                delete inventory[i];
            }
            if (other.inventory[i])
            {
                inventory[i] = other.inventory[i]->clone();
            }
            else
            {
                inventory[i] = NULL; // Use NULL instead of nullptr
            }
        }
    }
    return (*this);
}

Character::~Character()
{
    for (int i = 0; i < 4; ++i)
    {
        if (inventory[i])
        {
            delete inventory[i];
        }
    }
}

std::string const & Character::getName() const
 {
    return (name);
}

void Character::equip(AMateria* m)
{
    for (int i = 0; i < 4; ++i)
    {
        if (!inventory[i])
        {
            inventory[i] = m;
            break;
        }
    }
}

void Character::unequip(int idx)
{
    if (idx >= 0 && idx < 4)
    {
        inventory[idx] = NULL;
    }
}

void Character::use(int idx, ICharacter& target)
{
    if (idx >= 0 && idx < 4 && inventory[idx])
    {
        inventory[idx]->use(target);
    }
}