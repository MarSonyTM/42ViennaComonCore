/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:34:47 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/29 12:41:59 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>
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
};

std::ostream &operator<<(std::ostream &out, Form const &form);