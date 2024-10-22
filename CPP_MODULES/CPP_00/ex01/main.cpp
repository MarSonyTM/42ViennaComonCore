/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:17:57 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/26 18:50:39 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>

// main function provides the command line interface for interacting with the phone book application

int main(int ac, char **av)        
{
    if (ac > 1)
    {
        std::cout << "Usage: " << av[0] << std::endl;
        return (1);
    }
    
    PhoneBook phoneBook; // Creating an instance of the PhoneBook class
    std::string command; // variable to store the command entered by the user
    bool exit_flag = false; // Flag to catch cntrl + D and exit the program

    while (true) // Infinite loop to keep the program running
    {
        if (exit_flag)
        {
            break;
        }

        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
        std::getline(std::cin, command); // reads from the input stream and stores it in the command variable

        if (std::cin.eof())   // checks for cntrl + D
        {
            std::cout << "\nExiting..." << std::endl;
            break;
        }

        if (command == "ADD")
        {
            phoneBook.add_contact();
        }
        else if (command == "SEARCH")
        {
            phoneBook.search_contact(exit_flag);
        }
        else if (command == "EXIT")
        {
            break;
        }
        else
        {
            std::cout << "Unknown command. Please try again." << std::endl;
        }
    }
    return (0);
}