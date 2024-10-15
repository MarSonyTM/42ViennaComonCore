/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:28:33 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/15 14:05:46 by mafurnic         ###   ########.fr       */
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

    virtual void makeSound() const = 0; // Pure virtual function
    std::string getType() const;
};

#endif


/*
        This is the base class with a protected attribute type
        and a virtual function makeSounds(). The makeSound() function
        is meant to be overridden by derived classe like Dog and Cat in our examples.
*/