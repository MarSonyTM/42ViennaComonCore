/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:37:04 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 21:32:12 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(const std::string &name) : name(name), weapon(NULL) {}    // Constructor to initialize the name attribute and set the weapon to NULL

void HumanB::setWeapon(Weapon &weapon) // Setter for the weapon attribute
{
    this->weapon = &weapon;
}

void HumanB::attack() const
{
    if (weapon) // If the weapon is not NULL
        std::cout << name << " attacks with their " << weapon->getType() << std::endl;
    else
        std::cout << name << " has no weapon to attack with" << std::endl;
}