/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:34:47 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/31 13:19:56 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include "Bureaucrat.hpp"

class Form {
    private:
            std::string const _name;
            bool _signed;
            int const _gradeToSign;
            int const _gradeToExecute;

    public:
            Form();
            Form(std::string const &name, int _gradeToSign, int _gradeToExecute);
            Form(Form const &other);
            Form &operator=(Form const &other);
            ~Form();

            std::string const &getName() const;
            bool isSigned() const;
            int  getGradeToSign() const;
            int  getGradeToExecute() const;

            void beSigned(Bureaucrat const &bureaucrat);

            class GradeTooHighException : public std::exception {
                public:
                        virtual const char* what() const throw();
            };

            class GradeTooLowException : public std::exception {
                public:
                        virtual const char* what() const throw();
            };

            class FormAlreadySignedException : public std::exception {
                public:
                        virtual const char* what() const throw() {
                            return ("form is already signed");
                        }
            };
};

std::ostream &operator<<(std::ostream &out, Form const &form);