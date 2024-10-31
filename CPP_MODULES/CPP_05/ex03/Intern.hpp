/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:11:28 by marianfurni       #+#    #+#             */
/*   Updated: 2024/10/31 15:17:38 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern {
    private:
        // Function pointer type for form creation
        typedef AForm* (Intern::*FormCreator)(std::string const &target) const;
        
        // Array of form names and corresponding creation functions
        struct FormType {
            std::string name;
            FormCreator creator;
        };
        
        // Form creation methods
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