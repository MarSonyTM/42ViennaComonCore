/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:36:36 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 14:33:47 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

int main()
{
    int N = 5;
    Zombie* horde = zombieHorde(N, "HordeZombie"); // 1. Allocation of N zombies on the heap with a set name

    if(horde) // Check if the horde was created successfully
    {
        for(int i = 0; i < N; ++i)
        {
            horde[i].announce(); // 4. Call the announce method for each zombie in the horde
        } 
        delete[] horde; // 5. Deallocate the memory for the horde
    }
    else
    {
        std::cerr << "Failed to create zombie horde." << std::endl;
    }
    return (0);
}
