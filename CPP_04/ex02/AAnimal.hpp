/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:28:33 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/17 11:54:37 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_HPP
# define AANIMAL_HPP

#include <string>
#include <iostream>

class AAnimal
{
    protected:
      std::string type;

    public:
       AAnimal();
       AAnimal(AAnimal const &copy);
       AAnimal &operator = (AAnimal const &copy);
       virtual ~AAnimal();

    virtual void makeSound() const = 0; // Pure virtual function that makes the class abstract
    std::string getType() const;        // and cannot be instantiated directly.
};

#endif


/*
        This is the base class with a protected attribute type
        and a virtual function makeSounds().
        The class is abstract due to the pure virtual function makeSound.
*/