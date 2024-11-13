/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:18:34 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/13 15:50:11 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <iostream>

int main() {
    srand(time(0));  // Initialize random seed once at program start
    // Test multiple random generations
    std::cout << "Testing multiple random generations:" << std::endl;
    for (int i = 0; i < 5; i++) {
        Base* ptr = generate();
        
        std::cout << "\nTest " << i + 1 << ":" << std::endl;
        std::cout << "Using pointer: ";
        identify(ptr);
        
        std::cout << "Using reference: ";
        identify(*ptr);
        
        delete ptr;
    }

    // Test NULL pointer handling
    std::cout << "\nTesting NULL pointer:" << std::endl;
    Base* nullPtr = NULL;
    identify(nullPtr);

    return 0;
} 

/*
        The objective of this exercise is to create a function that generates a random class derived from Base,
        and two functions that identify the class using a pointer and a reference. The function generate()
        will return a pointer to a dynamically allocated object of a class derived from Base. 
        The function identify() will take a pointer to a Base object 
        and identify the derived class using dynamic_cast. 
        The function identify() will take a reference to a Base object
        and identify the derived class using try-catch blocks. 
        The main function will test the functions by generating a random class
        derived from Base and identifying it using the two functions.
        The main function will also test the functions with a NULL pointer.
*/