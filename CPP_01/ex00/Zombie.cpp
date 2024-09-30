/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:21:08 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 20:27:51 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(std::string name) : name(name) // Constructor to initialize the zombie with a name
{
    std::cout << "Zombie " << name << " has been created" << std::endl;
}

Zombie::~Zombie() // Destructor in this case is used to announce the destruction of the zombie
{
    std::cout << "Zombie " << name << " has been destroyed" << std::endl;
}

void Zombie::announce() const   // Method to announce the zombie
{
    std::cout <<  name << ": " << "BraiiiiiiinnnzzzZ..." << std::endl;
}
