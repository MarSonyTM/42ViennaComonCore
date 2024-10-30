/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:37:49 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/30 16:42:32 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string const &target)
    : AForm("PresidentialPardonForm", 25, 5), _target(target) {}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &other)
    : AForm(other), _target(other._target) {}

PresidentialPardonForm &PresidentialPardonForm::operator=(PresidentialPardonForm const &other){
    if (this != &other){
        AForm::operator=(other);
        _target = other._target;
    }
    return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm() {}

void PresidentialPardonForm::performAction() const 
{
   std:: cout << _target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}