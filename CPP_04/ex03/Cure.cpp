/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:11:00 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/22 11:12:17 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure() : AMateria("cure")
{
    std::cout << "Cure default constructor called" << std::endl;
}

Cure::Cure(const Cure &other) : AMateria(other)
{
    std::cout << "Cure copy constructor called" << std::endl;
}

Cure &Cure::operator = (const Cure &other)
{
    if (this != &other) 
    {
      AMateria::operator = (other);
    }
    std::cout << "Cure copy assignment operator called" << std::endl;
    return (*this);
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