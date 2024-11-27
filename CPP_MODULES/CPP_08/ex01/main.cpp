/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:53:07 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/27 14:06:50 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Span.hpp"

int main() {
    try {
        // Basic test from subject
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "Basic test" << std::endl;
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;

        // Test with 10,000 numbers
        Span bigSpan(10000);
        for (int i = 0; i < 10000; ++i) {
            bigSpan.addNumber(i * 2);  // Even numbers from 0 to 19998
        }
        std::cout << "\nBig span test:" << std::endl;
        std::cout << "Shortest span: " << bigSpan.shortestSpan() << std::endl;
        std::cout << "Longest span: " << bigSpan.longestSpan() << std::endl;

        // Test addRange
        Span rangeSpan(5);
        std::vector<int> numbers;
        numbers.push_back(1);
        numbers.push_back(2);
        numbers.push_back(3);
        numbers.push_back(4);
        numbers.push_back(5);
        rangeSpan.addRange(numbers.begin(), numbers.end());
        
        std::cout << "\nRange test:" << std::endl;
        std::cout << "Shortest span: " << rangeSpan.shortestSpan() << std::endl;
        std::cout << "Longest span: " << rangeSpan.longestSpan() << std::endl;

        // Test exceptions
        Span fullSpan(1);
        fullSpan.addNumber(1);
        fullSpan.addNumber(2);  // Should throw exception

        // Add this test to main.cpp
        std::vector<int> numbers1;
        for (int i = 1; i <= 5; ++i)
            numbers.push_back(i);

        Span sp1(10);
        try {
            // Add range of numbers efficiently
            sp.addRange(numbers.begin(), numbers.end());
            
            // Test spans
            std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
            std::cout << "Longest span: " << sp.longestSpan() << std::endl;
        } catch (std::exception& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
} 