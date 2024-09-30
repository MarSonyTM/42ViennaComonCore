/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:34:24 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 10:56:10 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name)     // Function to create a horde of zombies
{
    if (N <= 0)
        return (NULL);

    Zombie* horde = new Zombie[N]; // Allocate memory for N zombies explicitly using new operator
    for (int i = 0; i < N; ++i)
    {
        new(&horde[i]) Zombie(name); //2. Placement new operator to call the constructor explicitly for each zombie to set the name
    }
    return (horde); // 3.Return the pointer to the first zombie in the horde array
}