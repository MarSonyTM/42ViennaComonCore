/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:35:43 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 21:25:39 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

#include "Weapon.hpp"
#include <string>

class HumanB
{
    private:
        std::string name; // The name of the human
        Weapon *weapon; // Pointer to the weapon of the human 

    public:
        HumanB(const std::string &name); // Constructor to initialize the name attribute
        void setWeapon(Weapon &weapon); // Setter for the weapon attribute
        void attack() const; // Function to display the attack of the human
};

#endif