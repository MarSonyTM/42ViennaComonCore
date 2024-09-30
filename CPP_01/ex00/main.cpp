/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:30:02 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 10:25:47 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
    Zombie* zombie = newZombie("HeapZombie"); // creating a new zombie on the heap
    zombie->announce(); // zombie announces itself
    delete zombie; // Destructor is called here to free the memory allocated on the heap

    randomChump("StackZombie"); // creating a new zombie on the stack and announcing it
    return(0);
}

/* The exercise aims to teach the difference between creating objects on the stack and the heap.
    Stack Allocation - Suitable for short-lived objects, the memory is automatically freed when the object goes out of scope.
    Heap Allocation - Suitable for long-lived objects, the memory is not automatically freed and must be manually freed using delete.*/