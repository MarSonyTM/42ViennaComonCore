/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:39:18 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/07 14:00:00 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
    {
    Weapon club = Weapon("crude spiked club");   // Create a weapon object with the type "crude spiked club"
    HumanA bob("Bob", club);   // Create a human object with the name "Bob" and the weapon "club"
    
    bob.attack();  // Display the attack of the human "Bob" with the weapon "club"
    club.setType("some other type of club"); // Change the type of the weapon "club" to "some other type of club"
    bob.attack(); // Display the attack of the human "Bob" with the weapon "club"
    } 
    {
    Weapon club = Weapon("crude spiked club");  // Create a weapon object with the type "crude spiked club"
    HumanB jim("Jim"); // Create a human object with the name "Jim"
    
    jim.setWeapon(club); // Set the weapon of the human "Jim" to "club"
    jim.attack(); // Display the attack of the human "Jim" with the weapon "club"
    club.setType("some other type of club");    // Change the type of the weapon "club" to "some other type of club"
    jim.attack(); // Display the attack of the human "Jim" with the weapon "club"
    }
    
    return (0);
}

/*if the object (HUMAN) is guaranted to always have a weapon and the weapon
is provided at construction time best to use REFERNCE as it avoids null checks and ensures the object has a valid weapon*/

/*if the object (HUMAN) may not always have a weapon and the weapon can be changed or set dynamically 
best to use POINTER  to  the weapon , as it allows handling the absence of a weapon gracefully with NULL checks */
