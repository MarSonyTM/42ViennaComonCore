/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:04:21 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/30 15:44:48 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <string>
#include <iostream>

class AForm;

class Bureaucrat {
    private:
            std::string const _name;
            int _grade;

    public:
        Bureaucrat(std::string const &name, int grade);
        Bureaucrat(Bureaucrat const &other);
        Bureaucrat &operator=(Bureaucrat const &other);
        ~Bureaucrat();

        std::string const &getName() const;
        int     getGrade() const;
        void    incrementGrade();
        void    decrementGrade();
        void    signForm(AForm &form);
        void    executeForm(AForm const &form) const;
        
        class GradeTooHighException : public std::exception {     
            public:
                    virtual const char* what() const throw();
        };

        class GradeTooLowException : public std::exception {                                                                   
            public:
                    virtual const char * what() const throw();
        };  
};
    
std::ostream &operator<<(std::ostream &out, Bureaucrat const &bureucrat);