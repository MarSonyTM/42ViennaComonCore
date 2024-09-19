/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:45:11 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/19 14:52:20 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include <iostream>
#include <iomanip>
#include <cctype>

void Contact::setFirstName(const std::string &first_name) {
    this->first_name = first_name;
}

void Contact::setLastName(const std::string &last_name) {
    this->last_name = last_name;
}

void Contact::setNickname(const std::string &nickname) {
    this->nickname = nickname;
}

void Contact::setPhoneNumber(const std::string &phone_number) {
    this->phone_number = phone_number;
}

void Contact::setDarkestSecret(const std::string &darkest_secret) {
    this->darkest_secret = darkest_secret;
}

const std::string &Contact::getFirstName() const {
    return first_name;
}

const std::string &Contact::getLastName() const {
    return last_name;
}

const std::string &Contact::getNickname() const {
    return nickname;
}

const std::string &Contact::getPhoneNumber() const {
    return phone_number;
}

const std::string &Contact::getDarkestSecret() const {
    return darkest_secret;
}

bool Contact::is_valid_phone_number(const std::string &phone_number) const {
    if (phone_number.empty() || phone_number.length() < 5) {
        return false;
    }

    size_t start = 0;
    if (phone_number[0] == '+') {
        start = 1;
    }

    for (size_t i = start; i < phone_number.length(); ++i) {
        if (!std::isdigit(phone_number[i])) {
            return false;
        }
    }

    return true;
}

void Contact::set_contact_info() {
    std::string input;

    std::cout << "Enter first name: ";
    std::getline(std::cin, input);
    while (input.empty()) {
        std::cout << "First name cannot be empty. Enter first name: ";
        std::getline(std::cin, input);
    }
    setFirstName(input);

    std::cout << "Enter last name: ";
    std::getline(std::cin, input);
    while (input.empty()) {
        std::cout << "Last name cannot be empty. Enter last name: ";
        std::getline(std::cin, input);
    }
    setLastName(input);

    std::cout << "Enter nickname: ";
    std::getline(std::cin, input);
    while (input.empty()) {
        std::cout << "Nickname cannot be empty. Enter nickname: ";
        std::getline(std::cin, input);
    }
    setNickname(input);

    std::cout << "Enter phone number: ";
    std::getline(std::cin, input);
    while (input.empty() || !is_valid_phone_number(input)) {
        std::cout << "Phone number  must contain only digits (at least 4) and may start with a plus sign. Enter phone number: ";
        std::getline(std::cin, input);
    }
    setPhoneNumber(input);

    std::cout << "Enter darkest secret: ";
    std::getline(std::cin, input);
    while (input.empty()) {
        std::cout << "Darkest secret cannot be empty. Enter darkest secret: ";
        std::getline(std::cin, input);
    }
    setDarkestSecret(input);
}

void Contact::display_summary(int index) const {
    std::cout << std::setw(10) << index << "|"
              << std::setw(10) << (first_name.length() > 9 ? first_name.substr(0, 9) + "." : first_name) << "|"
              << std::setw(10) << (last_name.length() > 9 ? last_name.substr(0, 9) + "." : last_name) << "|"
              << std::setw(10) << (nickname.length() > 9 ? nickname.substr(0, 9) + "." : nickname) << std::endl;
}

void Contact::display_full_info() const {
    std::cout << "First Name: " << first_name << std::endl;
    std::cout << "Last Name: " << last_name << std::endl;
    std::cout << "Nickname: " << nickname << std::endl;
    std::cout << "Phone Number: " << phone_number << std::endl;
    std::cout << "Darkest Secret: " << darkest_secret << std::endl;
}