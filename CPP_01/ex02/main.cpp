/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:14:07 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/26 15:20:48 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main()
{
    std::string string = "HI THIS IS BRAIN";  // string
    std::string *stringPTR = &string;  // pointer to the string
    std::string &stringREF = string;  // reference to the string

    std::cout << "Address in memory of the string: " << &string << std::endl;   // address of the string
    std::cout << "Address in memory of the stringPTR: " << stringPTR << std::endl; // address of the pointer
    std::cout << "Address in memory of the stringREF: " << &stringREF << std::endl; // address of the reference

    std::cout << "String: " << string << std::endl; // string
    std::cout << "StringPTR: " << *stringPTR << std::endl; // string through the pointer
    std::cout << "StringREF: " << stringREF << std::endl;  // string through the reference

    return (0);
}