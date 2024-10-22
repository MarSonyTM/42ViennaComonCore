/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:30:02 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 20:45:51 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    Zombie *zombie; // Declaring a pointer to a Zombie object
    
    if (argc != 1 && argv)
    {
        std::cerr << "Usage: "<< argv[0] << std::endl;
        return (1);
    }
    zombie = newZombie("HeapZombie"); // creating a new zombie on the heap
    delete zombie; // Destructor is called here to announce the destruction of the zombie

    randomChump("StackZombie"); // creating a new zombie on the stack and announcing it
    return(0);
}

/* The exercise aims to teach the difference between creating objects on the stack and the heap.
    Stack Allocation - Suitable for short-lived objects, the memory is automatically freed when the object goes out of scope.
    Heap Allocation - Suitable for long-lived objects, the memory is not automatically freed and must be manually freed using delete.*/