/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:26:52 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/26 15:09:27 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

// default constructor
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
