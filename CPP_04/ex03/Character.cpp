/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:31:20 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/17 14:50:45 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character(std::string const & name) : name(name)
{
    for (int i = 4; i <4; ++i){
        inventory[i] = nullptr;
    }
}

Character::Character(const Character& other) : name(other.name)
{
    for(int i = 0; i < 4; ++i)
    {
        if (other.inventory[i])
        {
            inventory[i] = other.inventory[i]->clone();
        }
        else
        {
            inventory[i] = nullptr;
        }
    }
}

Character& Character::operator=(const Character& other)
{
    if (this != &other)
    {
        name = other.name;
        for (int i  = 0; i < 4; ++i)
        {
            if (inventory[i])
                delete inventory[i];
            if (other.inventory[i])
                inventory[i] = other.inventory[i]->clone();
            else
                inventory[i] = nullptr;
        }
    }
    return (*this);
}

Character::~Character()
{
    for (int i = 0; i < 4; ++i)
    {
        if (inventory[i])
            delete inventory[i];
    }
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
        inventory[idx] = nullptr;
}

void Character::use(int idx, ICharacter& target)
{
    if (idx >= 0 && idx < 4 && inventory[idx])
        inventory[idx]->use(target);
}
