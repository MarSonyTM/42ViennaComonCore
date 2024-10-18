/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:44:36 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/18 09:53:15 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Animal.hpp"
#include "Brain.hpp"

Dog::Dog() : Animal(), brain(new Brain())
{
    type = "Dog";
    std::cout << "Dog constructor called" << std::endl;
}

Dog::Dog(const Dog &copy) : Animal(copy), brain(new Brain(*copy.brain)) // deep copy of the brain
{
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog &Dog::operator = (const Dog &copy)
{
    if (this != &copy)
    {
        Animal::operator=(copy);
        delete brain; // delete the excisting brain to avoid memory leak
        brain = new Brain(*copy.brain); // Allocate new memory and copy the contents of the brain  
    }
    std::cout << "Dog assignation operator called" << std::endl;
    return (*this);
}

Dog::~Dog()
{
    delete brain;
    std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound () const
{
    std::cout << getType() << ": Woof! Woof!" << std::endl;
}