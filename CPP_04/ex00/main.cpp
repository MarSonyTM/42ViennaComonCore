/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:20:19 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/18 11:36:30 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    const Animal* animal = new Animal(); // animal object created with a pointer to the base class
    const Animal* Louis = new Dog(); // dog object created with a pointer to the base class
    const Animal* Ash = new Cat(); // cat object created with a pointer to the base class

    std::cout << "Louis is a " << Louis->getType() << " " << std::endl;
    std::cout << "Ash is a "<< Ash->getType() << " " << std::endl;
    Louis->makeSound();
    Ash->makeSound();
    animal->makeSound();

    delete animal;
    delete Louis;
    delete Ash;

    std::cout << "--------------------------" << std::endl;

    const WrongAnimal* wrongAnimal = new WrongAnimal(); // wrongAnimal object created with a pointer to the base class
    const WrongAnimal* wrongCat = new WrongCat(); // wrongCat object created with a pointer to the base class

    const WrongCat* wrongCat2 = new WrongCat(); // wrongCat object created with a pointer to the derived class

    std::cout << "WrongCat is type  " << wrongCat->getType() << " " << std::endl;
    wrongCat->makeSound();
    wrongAnimal->makeSound();
    wrongCat2->makeSound(); 

    delete wrongAnimal;
    delete wrongCat;
    delete wrongCat2;

    return(0);
}

/*
    Base Class Pointer to Base Class Object : Calls the base class's version of the function.
    Base Class Pointer to Derived Class Object : Calls the base class's version of the function if the function is not virtual.
    Derived Class Pointer to Derived Class Object : Calls the derived class's version of the function.
*/


/*
        Inheritance: Allows a class to inherit properties and behaviors from another class.
        Polymorphism: Enables methods to do different things bases on the object they are acting upon,
                      even if they share the same name.
        Virtual functions : Functions in a base class that can be overridden in derived classes.
                            When Called through a base class pointer or reference, the derived class's
                            version of the function is called.
        
*/