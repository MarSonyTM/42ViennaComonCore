/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:35:17 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/18 16:07:58 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal() : type("Animal") 
{
    std::cout << "Animal default constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal &copy)
{
    std::cout << "Animal copy constructor called" << std::endl;
    this->type = copy.type;
}

AAnimal &AAnimal::operator = (const AAnimal &copy)
{
    if (this != &copy)
        type = copy.type;
    std::cout << "Animal assignation oeperator called" << std::endl;
    return (*this);
}

AAnimal::~AAnimal()
{
    std::cout << "Animal destructor called" << std::endl;
}

void AAnimal::makeSound() const
{
    std::cout << getType() << " : makes a sound" << std::endl;
}

std::string AAnimal::getType() const
{
    return (this->type);
}