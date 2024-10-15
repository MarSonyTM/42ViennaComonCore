/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:42:33 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/15 12:01:39 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal
{
    public:
        Dog();
        Dog(const Dog &copy);
        Dog &operator = (const Dog &copy);
        virtual ~Dog();

        void makeSound() const;
};

#endif

/*
    Dog Class inherits from Animal class and sets the type to "Dog".
    It ovverrides the makeSound() functions to print a dog-specific Sound.
*/