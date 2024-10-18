/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:13:23 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/18 14:15:45 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    IMateriaSource* src = new MateriaSource();  // Create a MateriaSource object
    src->learnMateria(new Ice());               // Learn two types of Materia: Ice   adds Ice to the MateriaSource
    src->learnMateria(new Cure());              // and Cure                          adds Cure to the MateriaSource

    ICharacter* me = new Character("me");      // Create a Character object me
    AMateria* tmp;      // declare a pointer to AMateria                       

    tmp = src->createMateria("ice");          // Create and Equip the Character with the two types of Materia
    me->equip(tmp);                         // equip the Character me with Ice
    tmp = src->createMateria("cure");
    me->equip(tmp);                        // equip the Character me with Cure

    ICharacter* bob = new Character("bob");  // Create another Character object

    me->use(0, *bob); // Use the two types of Materia on the second Character 0 for Ice
    me->use(1, *bob); // 1 for Cure

    delete bob;
    delete me;             // Delete the Character objects
    delete src;

    return (0);
}

/*
      This program is designed to simulate a system where character can equip and use magical items called Materia.
      The key componets of the program are:
        Interface: ICharacter, IMateriaSource , design to be implemented by the Character and MateriaSource classes respectively
        Abstract class: AMateria
        Concrete classes: Ice, Cure
        Character class: Character
        MateriaSource class: MateriaSource

        The program is designed to be run in the following way:
            1. Create a MateriaSource object
            2. Learn two types of Materia: Ice and Cure
            3. Create a Character object
            4. Equip the Character with the two types of Materia
            5. Create another Character object
            6. Use the two types of Materia on the second Character
            7. Delete the Character objects
            8. Delete the MateriaSource object


    * Interface - A Class with pure virtual functions that define a contract fir the derived classes to implement
                    interface do not provide any implementation
    * Abstract class - A class that cannot be instantiated and is used to define the structure of derived classes
    * Concrete class - A class that can be instantiated and provides implementation for all the pure virtual functions of the base class
        
*/