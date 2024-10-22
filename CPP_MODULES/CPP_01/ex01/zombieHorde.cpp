/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:34:24 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 21:14:11 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
                      // function will return a pointer to the first zombie in the horde array
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