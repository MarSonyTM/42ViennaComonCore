/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:35:17 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/21 09:23:27 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal() : type("AAnimal") 
{
    std::cout << "AAnimal default constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal &copy)
{
    std::cout << "AAnimal copy constructor called" << std::endl;
    this->type = copy.type;
}

AAnimal &AAnimal::operator = (const AAnimal &copy)
{
    if (this != &copy)
        type = copy.type;
    std::cout << "AAnimal assignation oeperator called" << std::endl;
    return (*this);
}

AAnimal::~AAnimal()
{
    std::cout << "AAnimal destructor called" << std::endl;
}

void AAnimal::makeSound() const
{
    std::cout << getType() << " : makes a sound" << std::endl;
}

std::string AAnimal::getType() const
{
    return (this->type);
}