/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:49:22 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/15 14:06:37 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Cat_HPP
# define Cat_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public AAnimal 
{
    private:
        Brain* brain;

    public:
       Cat();
       Cat(const Cat &copy);
       Cat &operator = (const Cat &copy);
       virtual ~Cat();

    void makeSound() const; 
};

#endif

/*
        Cat Class inherits from Animal class and sets the type to "Cat".
        It overrides the function makeSound to print Cat specific sound.
*/