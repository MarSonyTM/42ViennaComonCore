/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:26:06 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 20:34:52 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
        
Zombie* newZombie(std::string name)  // Function returns a pointer to a Zombie object with the given name
{                    //new is a keyword in C++ that is used to allocate memory for an object on the heap
    Zombie* zombie = new Zombie(name); // Create a new Zombie object on the heap with the given name
    zombie->announce(); // Announce the zombie
    return (zombie); // Return the pointer to the new Zombie object
}