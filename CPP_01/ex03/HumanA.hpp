/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:32:50 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/26 15:55:43 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

#include "Weapon.hpp"
#include <string>

class HumanA
{
    private:
        std::string name; // The name of the human
        Weapon &weapon; // Reference to the weapon of the human

    public:
        HumanA(const std::string &name, Weapon &weapon); // Constructor to initialize the name and weapon attributes
        void attack() const; // Function to display the attack of the human

};

#endif