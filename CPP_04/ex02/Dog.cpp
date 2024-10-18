/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:44:36 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/18 16:08:33 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "AAnimal.hpp"
#include "Brain.hpp"

Dog::Dog() : AAnimal(), brain(new Brain())
{
    type = "Dog";
    std::cout << "Dog constructor called" << std::endl;
}

Dog::Dog(const Dog &copy) : AAnimal(copy), brain(new Brain(*copy.brain))
{
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog &Dog::operator = (const Dog &copy)
{
    if (this != &copy)
    {
        AAnimal::operator=(copy);
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