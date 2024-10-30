/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:04:21 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/30 19:44:59 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <string>
#include <iostream>

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
        
        class GradeTooHighException : public std::exception {     
            public:
                    virtual const char* what() const throw();
        };

        class GradeTooLowException : public std::exception {                                                                   
            public:
                    virtual const char * what() const throw();
        };  
};

std::ostream &operator<<(std::ostream &out, Bureaucrat const &bureaucrat);