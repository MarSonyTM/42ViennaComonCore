/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:20:19 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/15 13:07:15 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Cat.hpp"
#include "Dog.hpp"


int main()
{
    const Animal* animals[10];

    for (int i = 0; i < 5; ++i)
    {
        animals[i] = new Dog();
    }
    for (int i = 5; i < 10; ++i)
    {
        animals[i] = new Cat();
    }

    for (int i = 0; i < 10; ++i)
    {
        delete animals[i];
    }
     

    return(0);
}


/*
        Deep Copy : Ensures that copies of objects are deep copies, preventing memory issues.
        Inheritance: Allows a class to inherit propertie and behaviors from another class.
        Polymorphism: Enables methods to do different things bases on the object they are acting upon,
                      even if they share the same name.
        Virtual functions : Functions in a base class that can be overridden in derived classes.
                            When Called through a base class pointer or reference, the derived class's
                            versuib if tghe function is executed.
        
*/