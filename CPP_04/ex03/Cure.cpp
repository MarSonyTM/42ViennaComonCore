/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:11:00 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/18 13:45:59 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"
#include <iostream>

Cure::Cure() : AMateria("cure")
{
    std::cout << "Cure default constructor called" << std::endl;
}

Cure::Cure(const Cure &other) : AMateria(other)
{
    std::cout << "Cure copy constructor called" << std::endl;
}

Cure& Cure::operator=(const Cure &other)
{
    if (this != &other) {
        // Do not copy the type
        // Copy other relevant state if any
    }
    std::cout << "Cure copy assignment operator called" << std::endl;
    return *this;
}

Cure::~Cure()
{
    std::cout << "Cure destructor called" << std::endl;
}

AMateria* Cure::clone() const
{
    return (new Cure(*this)); // deep copy of the object
}

void Cure::use(ICharacter &target)   // Uses the materia on the target
{
    std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}