/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:42:33 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/17 12:02:38 by mafurnic         ###   ########.fr       */
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
   Abstract Class: The AAnimal class is abstract and cannpt be instantiated directly.
                   It has a pure virtual function makeSound. = 0;
*/