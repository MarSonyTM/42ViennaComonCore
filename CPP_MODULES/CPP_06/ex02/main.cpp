/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:18:34 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/06 13:53:39 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>

int main() {
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