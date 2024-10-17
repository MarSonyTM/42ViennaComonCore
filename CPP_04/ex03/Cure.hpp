/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:52:21 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/17 14:57:56 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

#include "AMateria.hpp"

class Cure : public AMateria {

    public:
            Cure();
            Cure(const Cure &other);
            Cure& operator=(const Cure &other);
            virtual ~Cure();

            AMateria* clone() const override;
            void use(ICharacter &target) override;
};

#endif