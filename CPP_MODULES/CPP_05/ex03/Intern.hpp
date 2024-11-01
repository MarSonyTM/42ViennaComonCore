/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:11:28 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/01 10:16:35 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern {
    private:
        // This defined a function pointer type that Returns AForm*, is a member function of Intern Class, Takes a const string reference as a parameter.
        typedef AForm* (Intern::*FormCreator)(std::string const &target) const;
        
        // Array of form names and corresponding creation functions
        struct FormType {                
            std::string name; // Name of the form
            FormCreator creator; // Pointer to the function that creates the form
        };
        
        // Form creation methods, are member functions of Intern Class ,
        AForm* createShrubberyForm(std::string const &target) const;
        AForm* createRobotomyForm(std::string const &target) const;
        AForm* createPresidentialForm(std::string const &target) const;

    public:
        Intern();  // Default constructor
        Intern(Intern const &other);  // Copy constructor
        Intern &operator=(Intern const &other);  // Assignment operator
        ~Intern();  // Destructor

        AForm* makeForm(std::string const &formName, std::string const &target) const;

        class FormNotFoundException : public std::exception {
            public:
                virtual const char* what() const throw();
        };
};