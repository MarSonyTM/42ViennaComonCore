/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:12:16 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/15 12:27:29 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iter.hpp"

// Function to increment an integer
void increment(int &x) {
    x += 1;
}

// Function to print an integer
void printInt(int &x) {
    std::cout << x << std::endl;
}

// Function to print a string
void printString(std::string &str) {
    std::cout << str << std::endl;
}

int main() {
    // Test with an array of integers
    int intArray[] = {1, 2, 3, 4, 5};
    int intArrayLength = sizeof(intArray) / sizeof(intArray[0]);

    std::cout << "Original int array:" << std::endl;
    iter(intArray, intArrayLength, printInt);
    std::cout << std::endl;

    iter(intArray, intArrayLength, increment);

    std::cout << "Incremented int array: " << std::endl;
    iter(intArray, intArrayLength, printInt);
    std::cout << std::endl;

    // Test with an array of strings
    std::string strArray[] = {"Hello", "World", "42", "is", "awesome"};
    int strArrayLength = sizeof(strArray) / sizeof(strArray[0]);

    std::cout << "String array: " << std::endl;
    iter(strArray, strArrayLength, printString);
    std::cout << std::endl;

    return 0;
}