/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:17:57 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/19 15:46:53 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>

int main(int ac, char **av)
{
    if (ac > 1)
    {
        std::cout << "Usage: " << av[0] << std::endl;
        return 1;
    }
    
    PhoneBook phoneBook;
    std::string command;
    bool exit_flag = false;

    while (true) {
        if (exit_flag) {
            break;
        }

        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
        std::getline(std::cin, command);

        if (std::cin.eof()) {
            std::cout << "\nExiting..." << std::endl;
            break;
        }

        if (command == "ADD") {
            phoneBook.add_contact();
        } else if (command == "SEARCH") {
            phoneBook.search_contact(exit_flag);
        } else if (command == "EXIT") {
            break;
        } else {
            std::cout << "Unknown command. Please try again." << std::endl;
        }
    }

    return 0;
}