/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:47:21 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/23 13:20:00 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <string>

class Contact {
private:                      // private members storing the data of the contact
    std::string first_name;
    std::string last_name;
    std::string nickname;                  // Defining Contact class which represents a individual contact in the PhoneBook
    std::string phone_number;
    std::string darkest_secret;

        // functions to validate and process the input data               // The const keyword  ensures that the phone number parameter cannot be modified withing the function 
    bool is_valid_phone_number(const std::string &phone_number) const;   // private member functions to validate the phone number
    bool is_valid_input(const std::string &input) const;  // private member functions to validate the input
    std::string trim(const std::string &str) const;   // private member functions to trim the string

public:     // Setters (mutators)
    void setFirstName(const std::string &first_name);
    void setLastName(const std::string &last_name);            // public member functions to set the contact information
    void setNickname(const std::string &nickname);
    void setPhoneNumber(const std::string &phone_number);
    void setDarkestSecret(const std::string &darkest_secret);

          // Getters (accessors)
    const std::string &getFirstName() const;   // by declaring a function const
    const std::string &getLastName() const;    //  we are telling the compiler that this function will not modify the object
    const std::string &getNickname() const;
    const std::string &getPhoneNumber() const;                  // public member functions to get the contact information
    const std::string &getDarkestSecret() const;

    void set_contact_info(); // function to set the contact information
    void display_summary(int index) const; // function to display the summary of the contact
    void display_full_info() const; // function to display the full information of the contact
};

#endif // CONTACT_HPP


