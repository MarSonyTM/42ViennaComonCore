/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:00:21 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/23 22:48:07 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

 // Constructor to initialize the PhoneBook class, it initializes the PhoneBook object, total_contacts and current_index
PhoneBook::PhoneBook() : total_contacts(0), current_index(0) {}

void PhoneBook::add_contact()
{
    if (total_contacts < 8)
    {
        contacts[total_contacts].set_contact_info();
        total_contacts++;
    }
    else
    {
        std::cout << "PhoneBook is full. Replacing the oldest contact." << std::endl;
        contacts[current_index].set_contact_info();
        current_index = (current_index + 1) % 8; // Circular buffer to replace the oldest contact
    }
}

void PhoneBook::search_contact(bool &exit_flag) const
{
    if (total_contacts == 0)
    {
        std::cout << "No contacts in the PhoneBook" << std::endl;
        return;
    }

    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    for (int i = 0; i < total_contacts; ++i)
    {
        contacts[i].display_summary(i + 1);
    }

    std::string input;
    while (true)
    {
        std::cout << "Enter the index of the contact you want to display or type 'EXIT' to return: ";
        std::getline(std::cin, input);

        if (std::cin.eof()) // Check for EOF (Ctrl + D)
        {
            std::cout << "\nExiting search..." << std::endl;
            std::cin.clear(); // Clear the EOF flag
            exit_flag = true;
            return;
        }

        if (input == "EXIT")
            return;

        std::stringstream ss(input);    // Convert the input to an integer
        int index;
        ss >> index; // Extract the integer from the stringstream

        // Check if the conversion was successful and the index is within the range, and there are no extra characters
        if (ss.fail() || index <= 0 || index > total_contacts || !ss.eof())
        {
            std::cout << "Invalid index. Please try again." << std::endl;
        }
        else
        {
            contacts[index - 1].display_full_info(); 
            break;
        }
    }
}