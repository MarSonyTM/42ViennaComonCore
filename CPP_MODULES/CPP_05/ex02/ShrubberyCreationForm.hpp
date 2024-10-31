/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:25:06 by marianfurni       #+#    #+#             */
/*   Updated: 2024/10/31 15:59:02 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"
#include <fstream> //   file operations

class ShrubberyCreationForm : public AForm {
    protected:
        void performAction() const;
    private:
        std::string _target;
    public:
        ShrubberyCreationForm();
        ShrubberyCreationForm(std::string const &target);
        ShrubberyCreationForm(ShrubberyCreationForm const &copy);
        ShrubberyCreationForm &operator=(ShrubberyCreationForm const &copy);
        virtual ~ShrubberyCreationForm();

        class FileOpenException : public std::exception {
            public:
                virtual const char* what() const throw();
        };

        class FileWriteException : public std::exception {
            public:
                virtual const char* what() const throw();
        };
};