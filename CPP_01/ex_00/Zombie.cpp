/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:21:08 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/26 13:00:31 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(std::string name) : name(name)
{
    std::cout << "Zombie " << name << " has been created" << std::endl;
}

Zombie::~Zombie()
{
    std::cout << "Zombie " << name << " has been destroyed" << std::endl;
}

void Zombie::announce()
{
    std::cout <<  name << ": " << "BraiiiiiiinnnzzzZ..." << std::endl;
}
