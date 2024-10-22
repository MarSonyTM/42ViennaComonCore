/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:17:14 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/22 11:33:45 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "AMateria.hpp" // Include the full definition of AMateria   

AMateria * Character::deleteMateria[];  // Initialize the static variable with a size of 1000

Character::Character() : name("default"), garbage()
{
    for (int i = 0; i < 4; ++i)
    {
        inventory[i] = NULL;       // Initialize the inventory with NULL pointers
    }
}
Character::Character(std::string const &name) : name(name), garbage()
{
    for (int i = 0; i < 4; ++i)
    {
        inventory[i] = NULL;    // Initialize the inventory with NULL pointers
    }
}

Character::Character(const Character &other) : name(other.name), garbage()
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
        for(int i = 0; i < 1000; i++)
        {
            if(garbage[i])
            {
                delete garbage[i];   // Delete the object
            }
        }
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
    for(int i = 0; i < 1000; i++)
    {
        if(garbage[i])
        {
            delete garbage[i];   // Delete the object
        }
    }
}

std::string const & Character::getName() const
{
    return (name);     // Return the name of the character
}

void Character::equip(AMateria* m)
{
    bool flag = true;
    
    if(!m)
    {
        std::cerr << "Error: No Materia!" << std::endl;
        return;
    }
    for (int i = 0; i < 1000; i++)
    {
        if (deleteMateria[i] == m)
        {
            flag = false;
            break;
        }
    }
    if(flag)
    {
        for(int i = 0; i < 1000; i++)
        {
            if(!deleteMateria[i] && i < 1000)
            {
                deleteMateria[i] = m;
                break;
            }
            else if (i == 999)
            {
                delete deleteMateria[i];
                deleteMateria[i] = m;
                break;
            }
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        if (!inventory[i])
        {
            inventory[i] = m->clone();    // Equip the materia to the first available slot in the inventory
            break;
        }
    }
}

void Character::unequip(int idx)
{
    if (idx >= 0 && idx < 4) // Check if the index is valid
    {
        for(int i = 0; i < 1000; i++)
        {
            if(!garbage[i] && i < 1000) 
            {
                garbage[i] = inventory[idx];   // Save the materia at the given index
                break;
            }
            else if (i == 999)
            {
                delete garbage[i];    // Delete the materia at the given index
                garbage[i] = inventory[idx];   // Save the materia at the given index
                break;
            }
        }
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