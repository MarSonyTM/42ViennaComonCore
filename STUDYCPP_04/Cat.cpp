/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:14:58 by marianfurni       #+#    #+#             */
/*   Updated: 2024/10/20 17:53:17 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal() {
    type = "Cat";
    std::cout << "Cat defult constructor called" << std::endl;
}

Cat::Cat(const Cat &copy) : Animal(copy) {
    std::cout << "Cat copy constructor called" << std::endl;
}

Cat &Cat::operator = (const Cat &copy){
    std::cout << "Cat copy asignment called" << std::endl;
    if (this != &copy)
        Animal::operator = (copy);
    return(*this);
}

Cat::~Cat(){
    std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound() const
{
    std::cout << getType() << " :Meow! Meow!" << std::endl;
}
