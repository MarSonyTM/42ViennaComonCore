/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:00:21 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/19 14:40:38 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

PhoneBook::PhoneBook() : total_contacts(0), current_index(0) {}

void PhoneBook::add_contact() {
    if (total_contacts < 8) {
        contacts[total_contacts].set_contact_info();
        total_contacts++;
    } else {
        std::cout << "PhoneBook is full. Replacing the oldest contact." << std::endl;
        contacts[current_index].set_contact_info();
        current_index = (current_index + 1) % 8;
    }
}

void PhoneBook::search_contact() const {
    if (total_contacts == 0) {
        std::cout << "No contacts in the PhoneBook" << std::endl;
        return;
    }

    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << std::endl;
    std::cout << "                                      " << std::endl;

    for (int i = 0; i < total_contacts; ++i) {
        contacts[i].display_summary(i + 1);
    }

    std::string input;
    while (true) {
        std::cout << "Enter the index of the contact you want to display or type 'EXIT' to return: ";
        std::getline(std::cin, input);

        if (input == "EXIT") {
            break;
        }

        std::stringstream ss(input);
        int index;
        ss >> index;

        if (ss.fail() || index <= 0 || index > total_contacts) {
            std::cout << "Invalid index. Please try again." << std::endl;
        } else {
            contacts[index - 1].display_full_info();
            break;
        }
    }
}