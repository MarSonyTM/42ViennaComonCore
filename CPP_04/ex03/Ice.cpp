/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:10:36 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/21 10:10:29 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
#include "ICharacter.hpp"
#include <iostream>

Ice::Ice() : AMateria("ice")
{
    std::cout << "Ice default constructor called" << std::endl;
}

Ice::Ice(const Ice &other) : AMateria(other)
{
    std::cout << "Ice copy constructor called" << std::endl;
}

Ice& Ice::operator=(const Ice &other)
{
    if (this != &other)
    {
        AMateria::operator=(other);
    }
    std::cout << "Ice copy assignment operator called" << std::endl;
    return (*this);
}

Ice::~Ice()
{
    std::cout << "Ice destructor called" << std::endl;
}

AMateria* Ice::clone() const
{
    return (new Ice(*this));  // deep copy of the object
}

void Ice::use(ICharacter &target)
{
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}