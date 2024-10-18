/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:54:50 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/18 09:53:21 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal(), brain(new Brain())
{
    type = "Cat";
    std::cout << "Cat constructor called" << std::endl;
}

Cat::Cat(const Cat &copy) : Animal(copy), brain(new Brain(*copy.brain)) // deep copy of the brain
{
    std::cout << "Cat copy constructor called" << std::endl;
}

Cat &Cat::operator = (const Cat &copy)
{
    if (this != &copy)
    {
        Animal::operator = (copy); // call the parent class assignment operator
        delete brain; // delete the old brain
        brain = new Brain(*copy.brain); // create a new brain and copy the content deep copy
    }
    std::cout << "Cat assignment operator called" << std::endl;
    return (*this); // return the current object by reference to allow chain assignment
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