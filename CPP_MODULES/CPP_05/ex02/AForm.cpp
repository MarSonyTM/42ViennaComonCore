/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:42:07 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/30 21:44:19 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm(std::string const &name, int gradeToSign, int gradeToExecute) 
    : _name(name), _signed(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
        if (gradeToSign < 1 || gradeToExecute < 1)
            throw GradeTooHighException();
        if (gradeToSign > 150 || gradeToExecute > 150)
            throw GradeTooLowException();
}

AForm::AForm(AForm const &other)
    : _name(other._name), _signed(other._signed), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {}

AForm &AForm::operator=(AForm const &other)
{
    if (this != &other)
        _signed = other._signed;
    return (*this);
}

AForm::~AForm() {};

std::string const &AForm::getName() const 
{
    return (_name);
}

bool AForm::isSigned() const
{
    return (_signed);
}

int AForm::getGradeToSign() const
{
    return (_gradeToSign);
}

int AForm::getGradeToExecute() const
{
    return (_gradeToExecute);
}

void AForm::beSigned(Bureaucrat const &bureaucrat)
{
    if (bureaucrat.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _signed = true;
}

const char* AForm::GradeTooHighException::what() const throw()
{
    return ("the grade it soo high!");
}

const char* AForm::GradeTooLowException::what() const throw()
{
    return ("grade is too low!");
}

const char* AForm::FormNotSignedException::what() const throw()
{
    return ("Form is not signed!");
}

std::ostream &operator<<(std::ostream &out, AForm const &form) 
{
    out << "Form " << form.getName() << ", signed: " << (form.isSigned() ? "yes" : "no")
    << ", grade to sign: " << form.getGradeToSign()
    << ", grade to execute: " << form.getGradeToExecute();

    return (out);
}

void AForm::execute(Bureaucrat const &executor) const
{
    if (!isSigned())
        throw FormNotSignedException();
    if (executor.getGrade() > getGradeToExecute())
        throw GradeTooLowException();
    performAction();
}


 