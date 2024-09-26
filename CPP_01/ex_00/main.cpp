/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:30:02 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/26 12:56:47 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
    Zombie* zombie = newZombie("HeapZombie"); // creating a new zombie on the heap
    zombie->announce(); // zombie announces itself
    delete zombie; // cleaning up to avoid memory leaks 

    randomChump("StackZombie"); // creating a new zombie on the stack and announcing it
    return(0);
}