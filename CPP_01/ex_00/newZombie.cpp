/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:26:06 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/26 13:13:30 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* newZombie(std::string name)
{                    //new is a keyword in C++ that is used to allocate memory for an object on the heap
    Zombie* zombie = new Zombie(name); // Create a new Zombie object on the heap
    return (zombie); // Return the pointer to the new Zombie object
}