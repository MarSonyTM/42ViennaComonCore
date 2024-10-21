/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:09:28 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/21 14:52:25 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

#include "ICharacter.hpp"                       
                                             // Character class implements ICharacter interface and repsresent a character in the game
class Character : public ICharacter {        // that can equip and use materia
private:
    std::string name;
    AMateria* inventory[4]; // 4 materia maximum , as per subject
public:
    static AMateria * deleteMateria[1000];
    AMateria * garbage[1000];
    Character();
    Character(std::string const &name);
    Character(const Character &other);
    Character& operator=(const Character &other);
    virtual ~Character();

    std::string const & getName() const;
    void equip(AMateria* m);   // Equip a materia to the first available slot in the inventory
    void unequip(int idx);    // Unequip the materia at the given index
    void use(int idx, ICharacter &target); // Use the materia at the given index on the target
};

#endif 