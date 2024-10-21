// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.cpp                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/18 11:13:23 by mafurnic          #+#    #+#             */
// /*   Updated: 2024/10/21 10:00:05 by mafurnic         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "MateriaSource.hpp"
// #include "Character.hpp"
// #include "Ice.hpp"
// #include "Cure.hpp"

// int main()
// {
//     IMateriaSource* src = new MateriaSource();  // Create a MateriaSource object
//     src->learnMateria(new Ice());               // Learn two types of Materia: Ice   adds Ice to the MateriaSource
//     src->learnMateria(new Cure());              // and Cure                          adds Cure to the MateriaSource

//     ICharacter* me = new Character("Cloud");      // Create a Character object me
//     AMateria* tmp;      // declare a pointer to AMateria                       

//     tmp = src->createMateria("ice");          // Create and Equip the Character with the two types of Materia
//     me->equip(tmp);                         // equip the Character me with Ice
//     tmp = src->createMateria("cure");
//     me->equip(tmp);                        // equip the Character me with Cure

//     ICharacter* bob = new Character("bob");  // Create another Character object

//     me->use(0, *bob); // Use the two types of Materia on the second Character 0 for Ice
//     me->use(1, *bob); // 1 for Cure

//     delete bob;
//     delete me;             // Delete the Character objects
//     delete src;

//     return (0);
// }

// /*
//       This program is designed to simulate a system where character can equip and use magical items called Materia.
//       The key componets of the program are:
//         Interface: ICharacter, IMateriaSource , design to be implemented by the Character and MateriaSource classes respectively
//         Abstract class: AMateria
//         Concrete classes: Ice, Cure
//         Character class: Character
//         MateriaSource class: MateriaSource

//         The program is designed to be run in the following way:
//             1. Create a MateriaSource object
//             2. Learn two types of Materia: Ice and Cure
//             3. Create a Character object
//             4. Equip the Character with the two types of Materia
//             5. Create another Character object
//             6. Use the two types of Materia on the second Character
//             7. Delete the Character objects
//             8. Delete the MateriaSource object


//     * Interface - A Class with pure virtual functions that define a contract fir the derived classes to implement
//                     interface do not provide any implementation
//     * Abstract class - A class that cannot be instantiated and is used to define the structure of derived classes
//     * Concrete class - A class that can be instantiated and provides implementation for all the pure virtual functions of the base class
        
// */



#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "ICharacter.hpp"
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include <cstdlib> 


void test_00()
{
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    ICharacter* me = new Character("me");
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    ICharacter* bob = new Character("bob");
    me->use(0, *bob);
    me->use(1, *bob);
    delete bob;
    delete me;
    delete src;
}

void test_01()
{
	std::cout << std::endl;
	std::cout << "CONSTRUCTORS:" << std::endl;
	std::cout << "-----------------------" << std::endl;
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter* me = new Character("me");
	std::cout << std::endl;

	// Create Materia
	std::cout << "CREATE MATERIA:" << std::endl;
	std::cout << "-----------------------" << std::endl;
	AMateria	*tmp;
	
	AMateria	*tmp1;
	AMateria	*tmp2;
	AMateria	*tmp3;

	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp1 = src->createMateria("cure");
	me->equip(tmp1);
	tmp = src->createMateria("fire"); // null
	me->equip(tmp);
	std::cout << std::endl;

	// // Use on a new character
	std::cout << "USE ON A NEW CHARACTER:" << std::endl;
	std::cout << "-----------------------" << std::endl;
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	std::cout << std::endl;
	me->use(2, *bob); // Use an empty / non existing slot in inventory
	me->use(-4, *bob);
	me->use(18, *bob);
	std::cout << std::endl;

	// Deep copy character
	std::cout << "DEEP COPY CHARACTER:" << std::endl;
	std::cout << "-----------------------" << std::endl;
	Character	*charles = new Character("Charles");
	tmp2 = src->createMateria("cure");
	charles->equip(tmp2);
	tmp3 = src->createMateria("ice");
	charles->equip(tmp3);
	tmp = src->createMateria("earth");
	charles->equip(tmp);
	Character	*charles_copy = new Character(*charles);
	std::cout << std::endl;

	// // Deep copy vs its source character
	// std::cout << "DEEP COPY VS SOURCE:" << std::endl;
	// std::cout << "-----------------------" << std::endl;
	// charles->unequip(0); // this shows that they have different materia pointers equipped
	// // charles_copy->unequip(1); //this will produce a leak if we don't store the address somewhere else before
	// tmp = src->createMateria("cure");
	// charles_copy->equip(tmp);
	// tmp = src->createMateria("ice");
	// charles_copy->equip(tmp);
	// std::cout << std::endl;

	charles->use(0, *bob);
	charles->use(1, *bob);
	charles->use(2, *bob);
	charles->use(3, *bob);
	std::cout << std::endl;
	charles_copy->use(0, *bob);
	charles_copy->use(1, *bob);
	charles_copy->use(2, *bob);
	charles_copy->use(3, *bob);
	std::cout << std::endl;

	// Unequip tests:
	std::cout << "UNEQUIP:" << std::endl;
	std::cout << "-----------------------" << std::endl;
	me->unequip(-1); // unequip an empty / non existing slot in inventory
	me->unequip(18);
	me->unequip(3);
	std::cout << std::endl;
	me->use(1, *charles);
	me->unequip(1); // Unequip a valid slot in inventory (cure unequipped)
	me->use(1, *charles); // try to use it
	std::cout << std::endl;

	// // Destructors
	// std::cout << "DESTRUCTORS:" << std::endl;
	// std::cout << "-----------------------" << std::endl;
	delete bob;
	delete me;
	delete src;
	delete charles;
	delete charles_copy;
	std::cout << std::endl;
}

void test_02()
{
	// {
	// 	IMateriaSource* src = new MateriaSource();
	// 	src->learnMateria(new Ice());
	// 	src->learnMateria(new Cure());
	// 	ICharacter* me = new Character("me");
	// 	AMateria* tmp;
	// 	tmp = src->createMateria("ice");
	// 	me->equip(tmp);
	// 	tmp = src->createMateria("cure");
	// 	me->equip(tmp);
	// 	ICharacter* bob = new Character("bob");
	// 	me->use(0, *bob);
	// 	me->use(1, *bob);
	// 	std::cout << std::endl;

	// 	delete bob;
	// 	delete me;
	// 	delete src;
	// }
	{
		std::cout << "1. Create new MateriaSource and learn materias (check maximum too):" << std::endl;
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		AMateria *mat = new Cure();
		src->learnMateria(mat);
		std::cout << std::endl;
		
		std::cout << "2. Create 2 new characters and test deep copy:" << std::endl;
		Character *dur0 = new Character("Alice");
		ICharacter *dur1 = new Character(*dur0);
		delete dur0;
		delete dur1;
		std::cout << std::endl;

		std::cout << "3. Create materias and equip them (also check unknown materias):" << std::endl;
		AMateria* tmp;
		ICharacter *dur2 = new Character("Alice");
		tmp = src->createMateria("ice");
		dur2->equip(tmp);
		tmp = src->createMateria("cure");
		dur2->equip(tmp);
		tmp = src->createMateria("hi");
		dur2->equip(tmp);
		delete src;
		std::cout << std::endl;

		std::cout << "4. Check maximum equipped too:" << std::endl;
		AMateria *cure = new Cure();
		AMateria *ice = new Ice();
		dur2->equip(cure);
		dur2->equip(cure);
		dur2->equip(ice);
		dur2->unequip(2);
		// delete cure; // Cure must be deleted manually when unequipped
		dur2->unequip(2);
		dur2->unequip(6);
		std::cout << std::endl;

		std::cout << "5. Use materias on new chacarter:" << std::endl;
		ICharacter* bob = new Character("Bob");
		dur2->use(0, *bob);
		dur2->use(1, *bob);
		dur2->use(2, *bob);
		dur2->use(6, *bob);
		dur2->use(-4, *bob);
		dur2->use(3, *bob);
		delete bob;
		std::cout << std::endl;

		delete dur2;
    }
}

void test_03()
{
	IMateriaSource*	src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter*	me = new Character("me");
	AMateria*	tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	me->equip(src->createMateria("cure"));
	me->equip(src->createMateria("cure"));
	me->equip(src->createMateria("cure"));
    me->unequip(3);
    me->unequip(2);
    me->unequip(4);
	tmp = src->createMateria("I DOESN'T exist");

	ICharacter*	bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	delete bob;
	delete me;
	delete src;
}

void test_04()
{
	// Create MateriaSource
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	// Create Character
	ICharacter* me = new Character("me");

	// Equip the character
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	for (int i = 0; i < 3; i++)  // Try to equip the same mat. object multiple times
		me->equip(tmp);
	for (int i = 0; i < 10; i++)  // Try to equip more than four materias
	{
		tmp = src->createMateria("ice");
		me->equip(tmp);
	}

	std::cout << std::endl << "Unequip some of them" << std::endl;
	for (int i = 6; i >= 2; i--)
		me->unequip(i);

	// Create target character and use the equipped materia on him
	ICharacter* bob = new Character("bob");
	std::cout << std::endl << "Use equipped materia on target bob" << std::endl;
	me->use(0, *bob);
	me->use(1, *bob);

	std::cout << std::endl << "Equipment after use:" << std::endl;

	delete bob;
	delete me;
	delete src;
}

void test_05()
{
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    ICharacter* me = new Character("me");
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    ICharacter* bob = new Character("bob");
    me->use(0, *bob);
    me->use(1, *bob);
    delete bob;
    delete me;
    delete src;
}


int subject()
{
	std::cout << std::endl << "---- LEARNING MATERIA -----" << std::endl << std::endl;
	
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	std::cout << std::endl << "---- CREATING MATERIA ----" << std::endl << std::endl;

	ICharacter* me = new Character("me");
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	std::cout << std::endl << "---- CHARACTER USING MATERIA ----" << std::endl << std::endl;

	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);

	std::cout << std::endl << "---- DELETING ... ----" << std::endl << std::endl;
	
	delete bob;
	delete me;
	delete src;

	return 0;
}

int subject_added()
{
	std::cout << std::endl << "---- LEARNING MATERIA -----" << std::endl << std::endl;

	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	std::cout << std::endl << "---- CREATING MATERIA ----" << std::endl << std::endl;

	ICharacter* me = new Character("me");
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	tmp = src->createMateria("ice");
	std::cout << "value of tmp: " << tmp << std::endl;
	me->equip(tmp);
	tmp = src->createMateria("cure");
	std::cout << "value of tmp: " << tmp << std::endl;
	me->equip(tmp);

	std::cout << std::endl << "---- CHARACTER USING MATERIA" << std::endl << std::endl;

	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	me->use(3, *bob);
	me->use(4, *bob);
	me->use(5, *bob);
	me->use(6, *bob);

	std::cout << std::endl << "---- UNEQUIP MATERIA ----" << std::endl << std::endl;

	me->unequip(1);
	bob->unequip(1);

	std::cout << std::endl << "---- DELETING ... ----" << std::endl << std::endl;

	delete bob;
	delete me;
	delete src;

	return 0;
}

int test_cpy_const()
{
	std::cout << std::endl << "---- LEARNING MATERIA -----" << std::endl << std::endl;

	IMateriaSource* mat1 = new MateriaSource(); // test copy constructor
	IMateriaSource* src = new MateriaSource(*static_cast<MateriaSource*>(mat1));
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	std::cout << std::endl << "---- CREATING MATERIA ----" << std::endl << std::endl;

	Character* me2 = new Character("me"); // test copy constructor
	ICharacter* me = new Character(*me2);
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	std::cout << std::endl << "---- CHARACTER USING MATERIA ----" << std::endl << std::endl;

	Character* bob2 = new Character("bob"); // test copy constructor
	ICharacter* bob = new Character(*bob2);
	me->use(0, *bob);
	me->use(1, *bob);

	std::cout << std::endl << "---- DELETING ... ----" << std::endl << std::endl;
	
	delete bob;
	delete me;
	delete src;
	delete mat1;
	delete me2;
	delete bob2;

	return 0;
}

int test_assignation()
{
	std::cout << std::endl << "---- LEARNING MATERIA -----" << std::endl << std::endl;

	IMateriaSource* mat1 = new MateriaSource(); // test assignation operator
	IMateriaSource* src = new MateriaSource();
	*static_cast<MateriaSource*>(src) = *static_cast<MateriaSource*>(mat1);
	*src = *mat1;
	
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	*dynamic_cast<MateriaSource*>(src) = *dynamic_cast<MateriaSource*>(mat1);

	std::cout << std::endl << "---- CREATING MATERIA ----" << std::endl << std::endl;

	Character* me2 = new Character("me"); // test assignation operator
	ICharacter* me = new Character(*me2);
	*dynamic_cast<Character*>(me) = *dynamic_cast<Character*>(me2);
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	std::cout << std::endl << "---- CHARACTER USING MATERIA ----" << std::endl << std::endl;

	Character* bob2 = new Character("bob2"); // test assignation operator
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	*dynamic_cast<Character*>(bob) = *dynamic_cast<Character*>(bob2);

	std::cout << std::endl << "---- DELETING ... ----" << std::endl << std::endl;

	delete bob;
	delete me;
	delete src;
	delete mat1;
	delete me2;
	delete bob2;

	return 0;
}

void test_06()
{
    IMateriaSource* ptr = new MateriaSource();
    ptr->learnMateria(new Ice());
    ptr->learnMateria(new Cure());
    IMateriaSource* src = new MateriaSource();
    IMateriaSource* temp;
    *src = *ptr;
    temp = src;
    src = new MateriaSource(*static_cast<MateriaSource*>(ptr));
    ICharacter* me = new Character("me");
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    ICharacter* bob = new Character("bob");
    me->use(0, *bob);
    me->use(1, *bob);
    delete bob;
    delete me;
    delete src;
    delete ptr;
    delete temp;
}

void	test_07_thomas()
{
	Character* bob = new Character("Bob");
	Character* jack = new Character("Jack");
	MateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	AMateria* ice = src->createMateria("ice");
	AMateria* cure = src->createMateria("cure");
	bob->equip(ice);
	bob->unequip(0);
	bob->equip(cure);
	jack->equip(ice);
	jack->unequip(0);
	delete bob;
	delete jack;
	delete src;
}

void	test_08_thomas()
{
	{
		std::cout << "\n---SECTION 1---\n" << std::endl;

		MateriaSource* src = new MateriaSource();
		AMateria* mat1 = new Ice();
		AMateria* mat2 = new Cure();
		src->learnMateria(mat1);
		src->learnMateria(mat1);
		src->learnMateria(mat2);
		src->learnMateria(mat2);

		std::cout << "\n---SECTION 2---\n" << std::endl;

		ICharacter* C1 = new Character("Tweedledee");
		ICharacter* C2 = new Character("Tweedledum");
		AMateria* tmp;


		std::cout << "\n---SECTION 3---\n" << std::endl;

		tmp = src->createMateria("ice");
		C1->equip(tmp);
		tmp = src->createMateria("cure");
		C1->equip(tmp);
		tmp = src->createMateria("ice");
		C1->equip(tmp);
		tmp = src->createMateria("cure");
		C1->equip(tmp);
		C2->equip(tmp);
		C1->equip(tmp);

		tmp = src->createMateria("cure");
		C2->equip(tmp);

		std::cout << "\n---SECTION 4---\n" << std::endl;

		C1->use(0, *C2);
		C2->use(0, *C1);

		std::cout << "\n---SECTION 5---\n" << std::endl;

		C1->unequip(0);
		C1->unequip(3);

		std::cout << "\n---SECTION 6---\n" << std::endl;

		ICharacter* C3 = new Character;
		*dynamic_cast<Character*>(C3) = *dynamic_cast<Character*>(C2);	// better use dynamic casting for downcasting Classes
		// dynamic_cast<Character*>(C3)->setName(C3->getName() + "_clone");

		std::cout << "\n---SECTION 7---\n" << std::endl;

		Character* C4 = new Character(*dynamic_cast<Character*>(C3));
		// C4->setName(C4->getName() + "_clone");

		std::cout << "\n---CLEANUP---\n" << std::endl;

		delete src;
		std::cout << std::endl;
		delete C1;
		std::cout << std::endl;
		delete C2;
		std::cout << std::endl;
		delete C3;
		std::cout << std::endl;
		delete C4;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	{
		std::cout << "\n---TESTS from subject---\n" << std::endl;
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		ICharacter* me = new Character("me");
		AMateria* tmp;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		ICharacter* bob = new Character("bob");
		me->use(0, *bob);
		me->use(1, *bob);

		std::cout << "\n---CLEANUP---\n" << std::endl;

		delete bob;
		delete me;
		delete src;
	}
}


void test_09()
{
    IMateriaSource* src = new MateriaSource();
    IMateriaSource* src2 = new MateriaSource();
	AMateria* tt = new Ice();

	src->learnMateria(tt);
    src->learnMateria(tt);
	src2->learnMateria(tt);

    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    ICharacter* me = new Character("me");
    ICharacter* bob = new Character("bob");
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
	bob->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
	me->unequip(1);
	me->unequip(0);
	me->unequip(0);
	me->equip(tmp);
	me->equip(tmp);
	me->equip(tmp);
	me->equip(tmp);
    me->use(0, *bob);
    me->use(1, *bob);
    delete bob;
    delete src;
	delete src2;
	delete me;
}

void test_10()
{
    IMateriaSource* src = new MateriaSource();
    for (int i = 0; i < 10; i++)
        src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    ICharacter* me = new Character("me");
    AMateria* tmp;
    for (int i = 0; i < 10; i++)
    {
        tmp = src->createMateria("ice");
        me->equip(tmp);    
    }
    tmp = src->createMateria("cure");
    me->equip(tmp);
    me->unequip(1);
    ICharacter* bob = new Character("bob");
    me->use(0, *bob);
    me->use(1, *bob);
    delete bob;
    delete me;
    delete src;
}

void test_11()
{
	IMateriaSource* src = new MateriaSource();
	AMateria* tt = new Ice();
	src->learnMateria(tt);
    // delete tt;
    // tt = NULL;
	src->learnMateria(tt);
	delete src;
	IMateriaSource* src2 = new MateriaSource();
	src2->learnMateria(tt);
	AMateria* tmp;
	tmp = src2->createMateria("ice");
	delete src2;
	ICharacter* me = new Character("me");
	me->equip(tmp);
	delete me;
}

void test_12()
{
    IMateriaSource* src = new MateriaSource();
    AMateria* tt = new Ice();
    src->learnMateria(tt);
    ICharacter* me = new Character("me");
    ICharacter* you = new Character("me");
    me->equip(tt);
    // you->equip(tt);
    delete me;
    delete you;
    delete src;
    // delete tt;
}

void test_13()
{
    IMateriaSource* src = new MateriaSource();
    AMateria* tt = new Ice();
    AMateria* bb = new Cure();
    AMateria* yy = new Ice();
    src->learnMateria(tt);
    src->learnMateria(bb);
    src->learnMateria(yy);
	src->learnMateria(new Ice());
    ICharacter* me = new Character("me");
    me->equip(tt);
    me->equip(bb);
    me->equip(yy);
    me->unequip(0);
    me->unequip(1);
    delete me;
    delete src;
}

int main()
{
    std::cout << "-----------Test00----------" << std::endl;
    test_00();
    std::cout << "-----------Test01----------" << std::endl;
    test_01();
    std::cout << "-----------Test02----------" << std::endl;
    test_02();
    std::cout << "-----------Test03----------" << std::endl;
    test_03();
    std::cout << "-----------Test04----------" << std::endl;
    test_04();
    std::cout << "-----------Test05----------" << std::endl;
    test_05();
    std::cout << "-----------Test06----------" << std::endl;
    test_06();
    std::cout << "-----------subject----------" << std::endl;
	subject();
    std::cout << "-----------subject_added----------" << std::endl;
	subject_added();
    std::cout << "-----------test_cpy_const----------" << std::endl;
	test_cpy_const();
    std::cout << "-----------test_assignation----------" << std::endl;
	test_assignation();
    std::cout << "-----------test_07_thomas----------" << std::endl;
	test_07_thomas();
    std::cout << "-----------test_08_thomas----------" << std::endl;
	test_08_thomas(); // segfault
    std::cout<< "-----------test_09----------" << std::endl;
	test_09();
    std::cout << "-----------test_10----------" << std::endl;
    test_10();
    std::cout << "-----------test_11----------" << std::endl;
	test_11(); // segfault
	std::cout << "-----------test_12----------" << std::endl;
    test_12();
    std::cout << "-----------test_13----------" << std::endl;
    test_13(); // segfault
	for (int i = 0; i < 1000; ++i) 
	{
		delete Character::deleteMateria[i];
	}
	bool flag = true;
	for (int i = 0; i < 1000; ++i) 
	{
		for(int j = 0; j < 1000; j++)
		{
			if(MateriaSource::learnMateriaAdress[i] == Character::deleteMateria[j])
			{
				flag = false;
				break;
			}
		}
		if(flag)
		{
			delete MateriaSource::learnMateriaAdress[i];
		}
		flag = true;
	}
	return 0;
}