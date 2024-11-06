/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:18:34 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/06 13:18:46 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <iostream>

int main() {
    Base* ptr = generate();
    
    std::cout << "Using pointer: ";
    identify(ptr);
    
    std::cout << "Using reference: ";
    identify(*ptr);
    
    delete ptr; 
    return 0;
} 