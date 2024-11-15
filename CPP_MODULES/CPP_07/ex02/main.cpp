/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:56:15 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/15 14:07:46 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Array.hpp"

int main() {
    // Testing default constructor
    Array<int> defaultArray;
    std::cout << "Default array size:" << defaultArray.size() << std::endl;

    // Testing constructor with size parameter
    Array<int> intArray(5);
    std::cout << "Int array size: " << intArray.size() << std::endl;

    // Testing subscript operator and exception handling
    try {
        for (unsigned int i = 0; i < intArray.size(); ++i) {
            intArray[i] = i * 2;
        }
        for (unsigned int i = 0; i < intArray.size(); ++i) {
            std::cout << "intArray[" << i << "] = " << intArray[i] << std::endl;
        }
        std::cout << "Accessing out of bounds element: " << intArray[10] << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }

    // Testing copy constructor
    Array<int> copyArray(intArray);
    std::cout << "Copy array size: " << copyArray.size() << std::endl;
    for (unsigned int i = 0; i < copyArray.size(); ++i){
        std::cout << "copyArray[" << i << "] = " << copyArray[i] << std::endl;
    }

    // Testing assignment operator
    Array<int> assignedArray;
    assignedArray = intArray;
    std::cout << "Assigned array size: " << assignedArray.size() << std::endl;
    for (unsigned int i = 0; i < assignedArray.size(); ++i) {
        std::cout << "assignedArray[" << i << "] = " << assignedArray[i] << std::endl;
    }

    // Test with string array
    Array<std::string> stringArray(3);
    stringArray[0] = "42";
    stringArray[1] = "is";
    stringArray[2] = "Awesome";
    
    std::cout << "\nString array test:" << std::endl;
    for (unsigned int i = 0; i < stringArray.size(); i++) {
        std::cout << stringArray[i] << " ";
    }
    std::cout << std::endl;

    // Test const array access
    const Array<int> constArray(3);
    try {
        std::cout << "\nConst array access test:" << std::endl;
        std::cout << constArray[0] << std::endl;  // Should work
        std::cout << constArray[5] << std::endl;  // Should throw
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    // Test deep copy
    Array<int> original(3);
    original[0] = 1;
    original[1] = 2;
    original[2] = 3;
    
    Array<int> copy = original;
    copy[0] = 100;  // Modify copy
    
    std::cout << "\nDeep copy test:" << std::endl;
    std::cout << "Original[0]: " << original[0] << std::endl;  // Should still be 1
    std::cout << "Copy[0]: " << copy[0] << std::endl;         // Should be 100

    return (0);
}

/*
        This excercise involves creating a class template Array that can store elements
        of any type and provides various functionalities sush as default construction,
        construction with a yize parameter, copy construction, asignment, element
        acces and size retrieval. The goal is to understand how to use templates to 
        create generic classes in C++.
*/