/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:13:12 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/18 13:53:24 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "MateriaSource.hpp"
#include "AMateria.hpp"

MateriaSource::MateriaSource()
{
    for (int i = 0; i < 4; ++i)
    {
        templates[i] = NULL;
    }
}

MateriaSource::MateriaSource(const MateriaSource &other)
{
    for (int i = 0; i < 4; ++i)
    {
        if (other.templates[i])
        {
            templates[i] = other.templates[i]->clone();
        }
        else
        {
            templates[i] = NULL;
        }
    }
}

MateriaSource& MateriaSource::operator=(const MateriaSource &other)
{
    if (this != &other)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (templates[i])
            {
                delete templates[i];
            }
            if (other.templates[i])
            {
                templates[i] = other.templates[i]->clone();
            }
            else
            {
                templates[i] = NULL;
            }
        }
    }
    return (*this);
}

MateriaSource::~MateriaSource()
{
    for (int i = 0; i < 4; ++i)
    {
        if (templates[i])
        {
            delete templates[i];
        }
    }
}

void MateriaSource::learnMateria(AMateria* m)    // this is a function is used to add a new materia to the MateriaSource
{                                               // by adding a new AMateria object to the templates array that can store up to 4 AMateria objects
    for (int i = 0; i < 4; ++i)
    {
        if (!templates[i]) // if the slot is empty
        {
            templates[i] = m; // add the materia
            break;
        }
    }
}

AMateria* MateriaSource::createMateria(std::string const & type)  // this function is used to create a new materia of the given type
{
    for (int i = 0; i < 4; ++i)
    {  // loop through the templates array
        if (templates[i] && templates[i]->getType() == type) // if the materia is found
        {
            return templates[i]->clone(); // return a deep copy of the materia
        }
    }
    return (NULL); // if the materia is not found return NULL
}