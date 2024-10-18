/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:17:14 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/18 13:46:51 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "AMateria.hpp" // Include the full definition of AMateria   

Character::Character() : name("default")
{
    for (int i = 0; i < 4; ++i)
    {
        inventory[i] = NULL;       // Initialize the inventory with NULL pointers
    }
}
Character::Character(std::string const &name) : name(name)
{
    for (int i = 0; i < 4; ++i)
    {
        inventory[i] = NULL;    // Initialize the inventory with NULL pointers
    }
}

Character::Character(const Character &other) : name(other.name)
{
    for (int i = 0; i < 4; ++i)
    {
        if (other.inventory[i])
        {
            inventory[i] = other.inventory[i]->clone();  // Deep copy of the object
        } 
        else
        {
            inventory[i] = NULL;
        }
    }
}

Character& Character::operator=(const Character &other)   // Deep copy of the object
{
    if (this != &other)
    {
        name = other.name; // Copy the name
        for (int i = 0; i < 4; ++i)
        {
            if (inventory[i])
            {
                delete inventory[i];   // Delete the current object
            }
            if (other.inventory[i])
            {
                inventory[i] = other.inventory[i]->clone();    // Deep copy of the object
            }
            else
            {
                inventory[i] = NULL;   // Set the pointer to NULL
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
            delete inventory[i];    // Delete the object
        }
    }
}

std::string const & Character::getName() const
{
    return (name);     // Return the name of the character
}

void Character::equip(AMateria* m)
{
    for (int i = 0; i < 4; ++i)
    {
        if (!inventory[i])
        {
            inventory[i] = m;    // Equip the materia to the first available slot in the inventory
            break;
        }
    }
}

void Character::unequip(int idx)
{
    if (idx >= 0 && idx < 4)
    {
        inventory[idx] = NULL;    // Unequip the materia at the given index
    }
}

void Character::use(int idx, ICharacter& target)
{
    if (idx >= 0 && idx < 4 && inventory[idx])
    {
        inventory[idx]->use(target);     // Use the materia at the given index on the target
    }
}