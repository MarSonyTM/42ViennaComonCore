/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:36:27 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/19 15:58:47 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "Contact.hpp"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>

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
    if (phone_number.empty()) {
        return false;
    }

    size_t start = 0;
    if (phone_number[0] == '+') {
        start = 1;
    }

    // Ensure the phone number has at least 4 digits excluding the '+'
    if (phone_number.length() - start < 4) {
        return false;
    }

    for (size_t i = start; i < phone_number.length(); ++i) {
        if (!std::isdigit(phone_number[i])) {
            return false;
        }
    }

    return true;
}

bool Contact::is_valid_input(const std::string &input) const {
    for (size_t i = 0; i < input.length(); ++i) {
        if (static_cast<unsigned char>(input[i]) > 127) {
            return false;
        }
    }
    return true;
}

std::string Contact::trim(const std::string &str) const {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

void Contact::set_contact_info() {
    std::string input;

    std::cout << "Enter first name: ";
    std::getline(std::cin, input);
    if (std::cin.eof()) exit(0);
    input = trim(input);
    while (input.empty() || !is_valid_input(input)) {
        std::cout << "First name cannot be empty and must contain only ASCII characters. Enter first name: ";
        std::getline(std::cin, input);
        if (std::cin.eof()) exit(0);
        input = trim(input);
    }
    setFirstName(input);

    std::cout << "Enter last name: ";
    std::getline(std::cin, input);
    if (std::cin.eof()) exit(0);
    input = trim(input);
    while (input.empty() || !is_valid_input(input)) {
        std::cout << "Last name cannot be empty and must contain only ASCII characters. Enter last name: ";
        std::getline(std::cin, input);
        if (std::cin.eof()) exit(0);
        input = trim(input);
    }
    setLastName(input);

    std::cout << "Enter nickname: ";
    std::getline(std::cin, input);
    if (std::cin.eof()) exit(0);
    input = trim(input);
    while (input.empty() || !is_valid_input(input)) {
        std::cout << "Nickname cannot be empty and must contain only ASCII characters. Enter nickname: ";
        std::getline(std::cin, input);
        if (std::cin.eof()) exit(0);
        input = trim(input);
    }
    setNickname(input);

    std::cout << "Enter phone number: ";
    std::getline(std::cin, input);
    if (std::cin.eof()) exit(0);
    input = trim(input);
    while (input.empty() || !is_valid_phone_number(input)) {
        std::cout << "Phone number must be at least 4 digits long, contain only digits, and may start with a plus sign. Enter phone number: ";
        std::getline(std::cin, input);
        if (std::cin.eof()) exit(0);
        input = trim(input);
    }
    setPhoneNumber(input);

    std::cout << "Enter darkest secret: ";
    std::getline(std::cin, input);
    if (std::cin.eof()) exit(0);
    input = trim(input);
    while (input.empty() || !is_valid_input(input)) {
        std::cout << "Darkest secret cannot be empty and must contain only ASCII characters. Enter darkest secret: ";
        std::getline(std::cin, input);
        if (std::cin.eof()) exit(0);
        input = trim(input);
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