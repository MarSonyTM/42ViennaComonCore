/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:34:24 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/26 14:26:52 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name)
{
    if (N <= 0)
        return (NULL);

    Zombie* horde = new Zombie[N];
    for (int i = 0; i < N; ++i)
    {
        new(&horde[i]) Zombie(name);
    }
    return (horde);
}