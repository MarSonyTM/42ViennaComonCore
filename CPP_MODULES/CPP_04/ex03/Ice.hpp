/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:10:30 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/18 13:48:27 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"
                                           // Concrete class Ice that inherits from AMateria
class Ice : public AMateria {
public:
    Ice();
    Ice(const Ice &other);
    Ice& operator=(const Ice &other);
    virtual ~Ice();

    AMateria* clone() const; // Returns a new instance of the materia
    void use(ICharacter &target); // Uses the materia on the target
};

#endif 