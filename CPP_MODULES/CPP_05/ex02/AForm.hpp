/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:34:47 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/30 18:59:27 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>
#include <string>
#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm {
    private:
            std::string const _name;
            bool _signed;
            int const _gradeToSign;
            int const _gradeToExecute;

    public:
            AForm();
            AForm(std::string const &name, int _gradeToSign, int _gradeToExecute);
            AForm(AForm const &other);
            AForm &operator=(AForm const &other);
            virtual ~AForm();

            std::string const &getName() const;
            bool isSigned() const;
            int  getGradeToSign() const;
            int  getGradeToExecute() const;

            void beSigned(Bureaucrat const &bureaucrat);
            virtual void execute(Bureaucrat const &executor) const = 0;

            class GradeTooHighException : public std::exception {
                public:
                        virtual const char* what() const throw();
            };

            class GradeTooLowException : public std::exception {
                public:
                        virtual const char* what() const throw();
            };

            class FormNotSignedException : public std::exception {
                public:
                        virtual const char* what() const throw();
            };
};

std::ostream &operator<<(std::ostream &out, AForm const &form);