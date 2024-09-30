/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:36:36 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 20:52:00 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

int main()
{
    int N; // Number of zombies in the horde
    Zombie* horde; // Pointer to an array of zombies
    
    N = 5;  
    horde = zombieHorde(N, "HordeZombie"); // 1. Allocation of N zombies on the heap with a set name

    if(horde) // Check if the horde was created successfully
    {
        for(int i = 0; i < N; ++i)
        {
            horde[i].announce(); // 4. Call the announce method for each zombie in the horde
        } 
        delete[] horde; // 5. Deallocate the memory for the horde array
    }
    else
    {
        std::cerr << "Failed to create zombie horde." << std::endl;
    }
    return (0);
}

/*
    Objective of this exercise:

    - Dynamically allocate an array of N zombies on the heap
    - Set the name of each zombie in the horde to the same name
    - Call the announce method for each zombie in the horde
    - Deallocate the memory for the horde array
*/
