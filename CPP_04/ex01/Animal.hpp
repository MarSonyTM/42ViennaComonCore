/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:28:33 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/15 12:00:27 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <string>
#include <iostream>

class Animal
{
    protected:
      std::string type;

    public:
       Animal();
       Animal(Animal const &copy);
       Animal &operator = (Animal const &copy);
       virtual ~Animal();

    virtual void makeSound() const;
    std::string getType() const;
};

#endif


/*
        This is the base class with a protected attribute type
        and a virtual function makeSounds(). The makeSound() function
        is meant to be overridden by derived classe like Dog and Cat in our examples.
*/