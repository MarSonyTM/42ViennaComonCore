/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:53:07 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/27 15:18:48 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Span.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

int main()
{
    try {
        // Test 1: Subject's test case
        std::cout << "=== Test 1: Subject's test ===" << std::endl;
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;

        // Test 2: 10,000 numbers test
        std::cout << "\n=== Test 2: 10,000 numbers test ===" << std::endl;
        Span bigSpan(10000);
        std::vector<int> numbers;
        
        srand(time(NULL));
        for (int i = 0; i < 10000; i++) {
            numbers.push_back(rand());
        }
        
        bigSpan.addRange(numbers.begin(), numbers.end());
        std::cout << "Shortest span: " << bigSpan.shortestSpan() << std::endl;
        std::cout << "Longest span: " << bigSpan.longestSpan() << std::endl;

        // Test 3: Exception cases
        std::cout << "\n=== Test 3: Exception cases ===" << std::endl;
        Span smallSpan(1);
        smallSpan.addNumber(5);
        try {
            smallSpan.addNumber(3);  // Should throw exception - span is full
        }
        catch (const std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }

        // Test empty span
        Span emptySpan(5);
        try {
            emptySpan.shortestSpan();  // Should throw - no numbers stored
        }
        catch (const std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }

        // Test 4: addRange functionality
        std::cout << "\n=== Test 4: addRange test ===" << std::endl;
        Span rangeSpan(5);
        std::vector<int> rangeTest;
        for (int i = 1; i <= 5; ++i)
            rangeTest.push_back(i);
            
        rangeSpan.addRange(rangeTest.begin(), rangeTest.end());
        std::cout << "Shortest span: " << rangeSpan.shortestSpan() << std::endl;
        std::cout << "Longest span: " << rangeSpan.longestSpan() << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }

    return 0;
} 