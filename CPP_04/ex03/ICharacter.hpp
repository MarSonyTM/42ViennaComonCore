/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICharacter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:09:11 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/22 10:55:52 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICHARACTER_HPP
#define ICHARACTER_HPP

#include <string>             //This Interface Defines the basic operations that a character can perform with materia

// Forward declaration of AMateria 
class AMateria;

class ICharacter {
public:
    virtual ~ICharacter() {}
    virtual std::string const & getName() const = 0;
    virtual void equip(AMateria* m) = 0; // Equip a materia to the first available slot in the inventory
    virtual void unequip(int idx) = 0;   // Unequip the materia at the given index
    virtual void use(int idx, ICharacter& target) = 0; // Use the materia at the given index on the target
};

#endif 