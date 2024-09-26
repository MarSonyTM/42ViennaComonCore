/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:36:36 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/26 15:10:48 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

int main()
{
    int N = 5;
    Zombie* horde = zombieHorde(N, "HordeZombie");

    if(horde)
    {
        for(int i = 0; i < N; ++i)
        {
            horde[i].announce();
        }
        delete[] horde;
    }
    else
    {
        std::cout << "Failed to create zombie horde." << std::endl;
    }
    return (0);
}