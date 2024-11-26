/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:54:26 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/26 13:54:27 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>

int main() {
    // Test with vector
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);

    try {
        // Should find 3
        std::vector<int>::iterator result = easyfind(vec, 3);
        std::cout << "Found value: " << *result << std::endl;

        // Should find 5
        result = easyfind(vec, 5);
        std::cout << "Found value: " << *result << std::endl;

        // Should throw exception
        result = easyfind(vec, 6);
        std::cout << "Found value: " << *result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test with list
    std::list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);

    try {
        // Should find 20
        std::list<int>::iterator result = easyfind(lst, 20);
        std::cout << "Found value: " << *result << std::endl;

        // Should throw exception
        result = easyfind(lst, 25);
        std::cout << "Found value: " << *result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
} 