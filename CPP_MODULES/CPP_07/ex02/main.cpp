/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:56:15 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/15 13:09:48 by mafurnic         ###   ########.fr       */
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
    return (0);
}