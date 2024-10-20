/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:47:24 by marianfurni       #+#    #+#             */
/*   Updated: 2024/10/20 18:07:26 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
const Animal* meta = new Animal();
std::cout << "object type " << meta->getType() << " " << std::endl;
meta->makeSound();std::cout << "-------------\n";
const Animal* j = new Dog();
std::cout << "object type " << meta->getType() << " " << std::endl;
j->makeSound(); std::cout << "-------------\n";
const Animal* i = new Cat();
std::cout << "object type " << meta->getType() << " " << std::endl;
i->makeSound(); std::cout << "-------------\n";
std::cout << "-------------\n";

std::cout << "And now we gonna demonstrate when polymorfism is not understood" << std::endl;


const WrongAnimal* wrongmeta = new WrongAnimal();
std::cout << "object type " << wrongmeta->getType() << " " << std::endl;
wrongmeta->makeSound(); std::cout << "-------------\n";
const WrongAnimal* Cat = new WrongCat();
std::cout << "object type " << wrongmeta->getType() << " " << std::endl;
Cat->makeSound(); std::cout << "-------------\n";

delete meta;
delete wrongmeta;
delete j;
delete i;
delete Cat;

return (0);
}