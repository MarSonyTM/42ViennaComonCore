/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:14:07 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 21:23:38 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main()
{
    std::string string = "HI THIS IS BRAIN";  // string
    std::string *stringPTR = &string;  // pointer to the string that holds the address of the string
    std::string &stringREF = string;  // reference to the string taht also refers to the string

    std::cout << "Address in memory of the string: " << &string << std::endl;   // address of the string
    std::cout << "Address in memory of the stringPTR: " << stringPTR << std::endl; // address of the pointer
    std::cout << "Address in memory of the stringREF: " << &stringREF << std::endl; // address of the reference

    std::cout << "String: " << string << std::endl; // string
    std::cout << "StringPTR: " << *stringPTR << std::endl; // string through the pointer
    std::cout << "StringREF: " << stringREF << std::endl;  // string through the reference

    return (0);
}

/*
    This exercise helps understand understand that references are just another way
    to manipulate adresses , similar to pointers. The difference is that references
    are not variables, they are just aliases for variables. They are not objects
    and they cannot be NULL. They are safer than pointers because they cannot be
    reassigned to another object after initialization.
*/