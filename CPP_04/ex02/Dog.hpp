/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:42:33 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/15 14:08:03 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal
{
    private:
        Brain* brain;
        
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