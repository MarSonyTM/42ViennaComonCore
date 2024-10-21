/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:13:00 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/21 13:21:16 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "ICharacter.hpp"
#include "IMateriaSource.hpp"              // MateriaSource class implements IMateriaSource interface and is responsible for learning and creating materia

class MateriaSource : public IMateriaSource {
private:
    AMateria* templates[4]; // 4 materia maximum, as per subject

public:
    static AMateria* learnMateriaAdress[1000];
    MateriaSource();
    MateriaSource(const MateriaSource &other);
    MateriaSource& operator=(const MateriaSource &other);
    virtual ~MateriaSource();

    void learnMateria(AMateria*);  // Learn a new type of materia
    AMateria* createMateria(std::string const & type); // Create a new instance of the materia
};

#endif