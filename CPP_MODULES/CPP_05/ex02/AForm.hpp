/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:34:47 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/30 16:54:44 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>
#include <string>
#include <iostream>
#include "Bureaucrat.hpp"

class AForm {
    private:
            std::string const _name;
            bool _signed;
            int const _gradeToSign;
            int const _gradeToExecute;

    public:
            AForm(std::string const &name, int _gradeToSign, int _gradeToExecute);
            AForm(AForm const &other);
            AForm &operator=(AForm const &other);
            virtual ~AForm();

            std::string const &getName() const;
            bool isSigned() const;
            int  getGradeToSign() const;
            int  getGradeToExecute() const;

            void beSigned(Bureaucrat const &bureaucrat);
            virtual void execute(Bureaucrat const &executor) const;
        

            class GradeTooHighException : public std::exception {
                public:
                        virtual const char* what() const throw();
            };

            class GradeTooLowException : public std::exception {
                public:
                        virtual const char* what() const throw();
            };
            
            class FormNotSignedException : std::exception {
                public:
                        virtual const char* what() const throw();
            };

        protected:
                virtual void performAction() const = 0;
};

std::ostream &operator<<(std::ostream &out, AForm const &form);