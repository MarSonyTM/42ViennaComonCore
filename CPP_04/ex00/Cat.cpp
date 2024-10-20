/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:54:50 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/20 13:56:12 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal()
{
    type = "Cat"; 
    std::cout << "Cat constructor called" << std::endl;
}

Cat::Cat(const Cat &copy) : Animal(copy)
{
    std::cout << "Cat copy constructor called" << std::endl;
}

Cat &Cat::operator = (const Cat &copy)
{
    if (this != &copy)
    {
        Animal::operator=(copy);
    }
    std::cout << "Cat assignment operator called" << std::endl;
    return (*this);
}

Cat::~Cat()
{
    std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound() const
{
    std::cout << getType() << " : Meow! Meow!" << std::endl;
}