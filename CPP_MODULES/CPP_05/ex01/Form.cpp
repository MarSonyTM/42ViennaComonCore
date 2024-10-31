/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:42:07 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/31 13:20:02 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form() : _name("Default"), _signed(false), _gradeToSign(150), _gradeToExecute(150) {}

Form::Form(std::string const &name, int gradeToSign, int gradeToExecute) 
    : _name(name), _signed(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
        if (gradeToSign < 1 || gradeToExecute < 1)
            throw GradeTooHighException();
        if (gradeToSign > 150 || gradeToExecute > 150)
            throw GradeTooLowException();
}

Form::Form(Form const &other)
    : _name(other._name), _signed(other._signed), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {}

Form &Form::operator=(Form const &other)
{
    if (this != &other) {
        _signed = other._signed;
    }
    return (*this);
}

Form::~Form() {};

std::string const &Form::getName() const 
{
    return (_name);
}

bool Form::isSigned() const
{
    return (_signed);
}

int Form::getGradeToSign() const
{
    return (_gradeToSign);
}

int Form::getGradeToExecute() const
{
    return (_gradeToExecute);
}

void Form::beSigned(Bureaucrat const &bureaucrat)
{
    if (_signed)
        throw FormAlreadySignedException();
    if (bureaucrat.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _signed = true;
}

const char* Form::GradeTooHighException::what() const throw()
{
    return ("Grade is too high!");
}

const char* Form::GradeTooLowException::what() const throw()
{
    return ("Grade is too low!");
}

std::ostream &operator<<(std::ostream &out, Form const &form) 
{
    out << "Form " << form.getName() << ", signed: " << (form.isSigned() ? "yes" : "no")
    << ", grade to sign: " << form.getGradeToSign()
    << ", grade to execute: " << form.getGradeToExecute();

    return (out);
}


 