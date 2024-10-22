/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:54:50 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/15 14:06:52 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : AAnimal(), brain(new Brain())
{
    type = "Cat";
    std::cout << "Cat constructor called" << std::endl;
}

Cat::Cat(const Cat &copy) : AAnimal(copy), brain(new Brain(*copy.brain))
{
    std::cout << "Cat copy constructor called" << std::endl;
}

Cat &Cat::operator = (const Cat &copy)
{
    if (this != &copy)
    {
        AAnimal::operator=(copy);
        delete brain;
        brain = new Brain(*copy.brain);
    }
    std::cout << "Cat assignment operator called" << std::endl;
    return (*this);
}

Cat::~Cat()
{
    delete brain;
    std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound() const  
{
    std::cout << getType() << " : Meow! Meow!" << std::endl;
}