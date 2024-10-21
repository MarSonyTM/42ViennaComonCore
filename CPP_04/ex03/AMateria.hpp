/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:08:19 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/21 09:37:05 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>
#include <iostream>
#include "ICharacter.hpp"
                                        // Abstract class AMateria that is the base class for all materia 
class AMateria {
protected:
    std::string type;   // The materia type

public:
    AMateria();
    AMateria(std::string const &type);
    AMateria(const AMateria &other);
    AMateria& operator=(const AMateria &other);
    virtual ~AMateria();

    std::string const & getType() const; // Returns the materia type
    virtual AMateria* clone() const = 0; // Returns a new instance of the materia ,pure virtual function
    virtual void use(ICharacter &target); // Uses the materia on the target
};

#endif 