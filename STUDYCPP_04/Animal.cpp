/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:05:16 by marianfurni       #+#    #+#             */
/*   Updated: 2024/10/20 14:00:41 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : type("Animal") {
    std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(const Animal &copy) {
    std::cout << "Animal copy constructor called" << std::endl;
    this->type = copy.type;
}

Animal &Animal::operator = (const Animal &copy) {
    if (this != &copy)
        this->type = copy.type;
    return (*this);
}

Animal::~Animal() {
    std::cout << "Animal destructor called" << std::endl;
}

void Animal::makeSound() const {
    std::cout << "Animal makes sound" << std::endl;
}

std::string Animal::getType() const {
    return (this->type);
}