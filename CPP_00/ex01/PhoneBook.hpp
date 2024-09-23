/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:51:17 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/23 18:17:28 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"

// Defining PhoneBook Class  which manages a collection of contacts

class PhoneBook {
private:
    Contact contacts[8];
    int total_contacts;  
    int current_index;

public:
    PhoneBook();  // constructor to initialize the PhoneBook class, it initializes the PhoneBook object.
 
    void add_contact();
    void search_contact(bool &exit_flag) const; // the & symbol is used to pass the variable by reference , meaning that the function can modify the variable
};

#endif // PHONEBOOK_HPP