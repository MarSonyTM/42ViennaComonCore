/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:13:12 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/21 15:30:09 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "AMateria.hpp"

AMateria* MateriaSource::learnMateriaAdress[];

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
        if (other.templates[i]) // if the slot is not empty
        {
            templates[i] = other.templates[i]->clone(); // deep copy the materia
        }
        else
        {
            templates[i] = NULL; // if the slot is empty
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

void MateriaSource::learnMateria(AMateria* m)    // this is a function is used to add a new materia to the MateriaSource templates
{                      
    bool flag = true;
    
    if(!m)
    {
        std::cerr << "Error: No Materia!" << std::endl;
        return;
    }        
    for (int i = 0; i < 1000; i++)
    {
        if (learnMateriaAdress[i] == m)
        {
            flag = false;
            break;
        }
    }
    if(flag)
    {
                         // by adding a new AMateria object to the templates array that can store up to 4 AMateria objects
        for(int i = 0; i < 1000; i++)
        {
            if(!learnMateriaAdress[i] && i < 1000)
            {
                learnMateriaAdress[i] = m;
                break;
            }
            else if (i == 999)
            {
                delete learnMateriaAdress[i];
                learnMateriaAdress[i] = m;
                break;
            }
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        if (!templates[i]) // if the slot is empty
        {
            templates[i] = m->clone(); // add the materia
            break;
        }                                
    }
}

AMateria* MateriaSource::createMateria(std::string const & type)  // this function is used to create a new materia based of the type passed as an argument
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