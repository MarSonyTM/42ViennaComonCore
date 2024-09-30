/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:39:01 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 22:35:20 by marianfurni      ###   ########.fr       */
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
    Harl harl; // Create an instance of the Harl class
    std::string levels; // Variable to store the log level entered by the user
    while(1)
    {
        std::cout << "Enter the log level:<DEBUG, INFO, WARNING, ERROR>: ";
        std::cin >> levels; // Read the log level from the user
        if (levels == "EXIT" || std::cin.eof()) // Check if the user wants to exit or the end of file is reached cntrl + D
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