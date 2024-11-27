/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:54:26 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/27 12:19:34 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp" // easyfind
#include <iostream> // std::cout
#include <vector>   // std::vector
#include <list>    // std::list
#include <climits>  // INT_MIN, INT_MAX

int main(void)
{
    // Original tests
    std::vector<int> numbers;
    for (int i = 1; i <= 5; i++)
        numbers.push_back(i * 10);  // Creates {10, 20, 30, 40, 50}

    // Test 1: Finding existing value in vector
    try
    {
        std::vector<int>::iterator it = easyfind(numbers, 30);
        std::cout << "Test 1 - Found value: " << *it << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Test 1 Error: " << e.what() << std::endl;
    }

    // Test 2: Finding non-existing value in vector
    try
    {
        std::vector<int>::iterator it = easyfind(numbers, 25);
        std::cout << "Test 2 - Found value: " << *it << std::endl;
    }
    catch (std::exception& e) 
    {
        std::cout << "Test 2 Error: " << e.what() << std::endl;
    }

    // Edge Cases:

    // Test 3: Empty container
    std::vector<int> empty_vec;
    try
    {
        std::vector<int>::iterator it = easyfind(empty_vec, 1);
        std::cout << "Test 3 - Found value: " << *it << std::endl;
    }

    catch (std::exception& e)
    {
        std::cout << "Test 3 Error: " << e.what() << std::endl;
    }

    // Test 4: Container with negative numbers
    std::list<int> negative_nums;
    negative_nums.push_back(-100);
    negative_nums.push_back(-200);
    negative_nums.push_back(-300);

    try
    {
        std::list<int>::iterator it = easyfind(negative_nums, -200);
        std::cout << "Test 4 - Found value: " << *it << std::endl;
    }
    
    catch (std::exception& e)
    {
        std::cout << "Test 4 Error: " << e.what() << std::endl;
    }

    // Test 5: Container with duplicate values
    std::vector<int> duplicates;
    duplicates.push_back(42);
    duplicates.push_back(42);
    duplicates.push_back(42);

    try
    {
        std::vector<int>::iterator it = easyfind(duplicates, 42);
        std::cout << "Test 5 - Found first occurrence of: " << *it << std::endl;
    }
    
    catch (std::exception& e)
    {
        std::cout << "Test 5 Error: " << e.what() << std::endl;
    }

    // Test 6: Finding INT_MAX
    std::list<int> extreme_values;
    extreme_values.push_back(INT_MAX);
    extreme_values.push_back(INT_MIN);

    try
    {
        std::list<int>::iterator it = easyfind(extreme_values, INT_MAX);
        std::cout << "Test 6 - Found extreme value: " << *it << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Test 6 Error: " << e.what() << std::endl;
    }

    return (0);
} 

/*
    Standard containters in C++ are part of the Standard Template Library (STL).
    They provide a way to store nad manage collections of data. The most common
    containers are: vector, list, queue, stack, map, set, etc.


    1. Vector - Dynamic array that can grow and shrink in size.
                Provides fast random access and efficient insetion/removal at the end.

    2. List - Doubly linked list. Provides efficient insetion/removal at both ends and at any position,
                but slower random access.

    3. Deque - Double ended queue. Provides fast insertion/removal at both ends and efficient random access.
    
    4. Set -  Ordered collection of unique elements. Provides fast lookup, insertion, and removal.

    5. Map - Ordered collection of key-value pairs. Provides fast lookup, insertion, and removal based on keys.


    Associative Containers:
    
        Associative containers are a subset of standard containers that provide fast retrieveal of data based on key.
        They are implemented as balanced binary search trees, and include the following containers.
*/