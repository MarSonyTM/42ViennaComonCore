/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:54:26 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/26 15:22:55 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

int main(void)
{
    // Test with vector
    std::vector<int> numbers;
    for (int i = 1; i <= 5; i++)
        numbers.push_back(i * 10);  // Creates {10, 20, 30, 40, 50}

    // Test 1: Finding existing value in vector
    try {
        std::vector<int>::iterator it = easyfind(numbers, 30);
        std::cout << "Test 1 - Found value: " << *it << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Test 1 Error: " << e.what() << std::endl;
    }

    // Test 2: Finding non-existing value in vector
    try {
        std::vector<int>::iterator it = easyfind(numbers, 25);
        std::cout << "Test 2 - Found value: " << *it << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Test 2 Error: " << e.what() << std::endl;
    }

    // Test with list
    std::list<int> lst;
    lst.push_back(100);
    lst.push_back(200);
    lst.push_back(300);

    // Test 3: Finding existing value in list
    try {
        std::list<int>::iterator it = easyfind(lst, 200);
        std::cout << "Test 3 - Found value: " << *it << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Test 3 Error: " << e.what() << std::endl;
    }

    // Test 4: Finding non-existing value in list
    try {
        std::list<int>::iterator it = easyfind(lst, 150);
        std::cout << "Test 4 - Found value: " << *it << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Test 4 Error: " << e.what() << std::endl;
    }

    return (0);
} 