/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:39:01 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 22:12:26 by marianfurni      ###   ########.fr       */
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
    Harl harl;
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
        harl.filter(levels); // Call the complain function to output the message based on the log level
    }
    

    return (0);
}

/*
        The Goal of this excercise if to create a programm that filters
        and displays messages from a character named Harl based on a specific log level.
        The prgramm should display mesagges staring from the specified log level up to the highest level (ERROR).
*/