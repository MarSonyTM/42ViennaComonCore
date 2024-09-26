/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:39:18 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/26 16:05:12 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
    {
    Weapon club = Weapon("crude spiked club");   // Create a weapon
    
    HumanA bob("Bob", club);   // Create a human with the weapon
    bob.attack();
    club.setType("some other type of club");
    bob.attack();
    }
    {
    Weapon club = Weapon("crude spiked club");
    
    HumanB jim("Jim");
    jim.setWeapon(club);
    jim.attack();
    club.setType("some other type of club");
    jim.attack();
    }
    
    return (0);
}

/*if the object (HUMAN) is guaranted to always have a weapon and the weapon
is provided at construction time best to use REFERNCE as it avoids null checks and ensures the object has a valid weapon*/

/*if the object (HUMAN) may not always have a weapon and the weapon can be changed or set dynamically 
best to use POINTER  to  the weapon , as it allows handling the absence of a weapon gracefully with NULL checks */
