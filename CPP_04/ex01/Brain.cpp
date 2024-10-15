/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:32:51 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/15 12:38:36 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
    std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(const Brain &copy)
{
    std::cout << "Brain copy constructor called" << std::endl;
    for(int i = 0; i < 100; ++i)
    {
        this->ideas[i] = copy.ideas[i];
    }
}

Brain &Brain::operator = (const Brain &copy)
{
    std::cout << "Brain assignment operator called" << std::endl;
    if (this != &copy)
    {
        for(int i = 0; i < 100; ++i)
        {
            this->ideas[i] = copy.ideas[i];
        }
    }
    return (*this);   
}

Brain::~Brain()
{
    std::cout << "Brain destructor called" << std::endl;
}

