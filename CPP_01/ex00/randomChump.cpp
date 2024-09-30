/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:27:35 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 20:29:10 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void randomChump(std::string name)
{
    Zombie zombie(name); // create a zombie on the stack with the given name
    zombie.announce(); // zombie announces itself
} // Destructor is called automatically  here once the function goes out of scope and the zombie is destroyed

