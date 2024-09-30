/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:08:34 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 22:06:02 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 1)
    {
        std::cerr << "Usage: " << argv[0] << std::endl;
        return (1);
    }
    Harl harl; // Creata a instance of the Harl class

    std::string levels;
    while(1)
    {
        std::cout << "Enter the log level:<DEBUG, INFO, WARNING, ERROR>: ";
        std::cin >> levels;
        if (levels == "EXIT" || std::cin.eof())
        {
            std::cerr << "Exiting..." << std::endl;
            break;
        }
        harl.complain(levels); // Call the complain function to output the message based on the log level
    }
    return (0);
}

/*
    The Goal of this exercise is to create a Harl Class that can output different messages
    based on a given log level. The log levels are DEBUG, INFO, WARNING and ERROR.
    The Harl class should use pointers to member functions to call the apporproate function based on the log level.
    avoiding the use of series of if/else statements.

*/