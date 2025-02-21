/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:10:49 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/18 13:46:13 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
#define CURE_HPP
 
#include "AMateria.hpp"                               // Concrete class Cure that inherits from AMateria

class Cure : public AMateria {
public:
    Cure();
    Cure(const Cure &other);
    Cure& operator=(const Cure &other);
    virtual ~Cure();

    AMateria* clone() const;
    void use(ICharacter &target);
};

#endif