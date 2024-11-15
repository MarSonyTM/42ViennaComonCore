/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:12:16 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/15 14:53:26 by marianfurni      ###   ########.fr       */
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

// Add this function
void printConstInt(const int &x) {
    std::cout << x << std::endl;
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

    // Add this test:
    const int constArray[] = {10, 20, 30, 40, 50};
    std::cout << "Const array test:" << std::endl;
    iter(constArray, 5, printConstInt);

    return 0;
}

/*
    The exercise requires creating a template function iter that iterates 
    through an array and applies a function to each element.
*/