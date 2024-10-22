/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:29:37 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/26 15:46:19 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(const std::string &type) : type(type) {}   // Constructor to initialize the type attribute

const std::string &Weapon::getType() const            // Getter for the type attribute
{
    return (type);
}

void Weapon::setType(const std::string &type)    // Setter for the type attribute
{
    this->type = type;
}