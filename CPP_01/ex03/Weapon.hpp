/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:28:23 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/26 15:46:04 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <string>

class Weapon
{
private:
    std::string type; // The type of the weapon

public:
    Weapon(const std::string &type); // Constructor to initialize the type attribute
    const std::string &getType() const; // Getter for the type attribute
    void setType(const std::string &type);  // Setter for the type attribute
};

#endif