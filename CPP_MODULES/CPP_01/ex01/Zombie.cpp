/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:26:52 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 21:15:49 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

// default constructor with name set to empty string to initialize the zombie with an empty name to avoid undefined behavior
Zombie::Zombie() : name("") {}

// parameterized constructor 
Zombie::Zombie(std::string name) : name(name)
{
    std::cout << "Zombie " << this->name << " is created." << std::endl;
}

// destructor
Zombie::~Zombie()
{
    std::cout << "Zombie " << this->name << " is destroyed." << std::endl;
}

// announce method
void Zombie::announce() 
{
    std::cout << this->name << "> BraiiiiiiinnnzzzZ..." << std::endl;
}
