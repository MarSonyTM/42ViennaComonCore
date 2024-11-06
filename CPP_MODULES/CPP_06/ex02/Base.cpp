/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:18:22 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/06 16:03:06 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
#include <iostream>
#include <typeinfo>  // For typeid


Base::~Base() {}

Base* generate(void) {
    srand(time(NULL));  // Seed random number generator
    int random = rand() % 3;  // Generate 0, 1, or 2

    switch (random) {
        case 0: return new A();
        case 1: return new B();
        case 2: return new C();
        default: return NULL;
    }
}

// This function uses dynamic_cast to identify the derived class of the Base object
void identify(Base* p) {
    if (!p) {
        std::cout << "NULL pointer" << std::endl;
        return;
    }
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}


// This function uses try-catch blocks to identify the derived class of the Base object
void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (std::bad_cast&) {}
    
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (std::bad_cast&) {}
    
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (std::bad_cast&) {}
} 