/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:31:48 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/30 16:41:35 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string const &target)
    : AForm("Robotomy Request", 72, 45), _target(target) {
    std::srand(std::time(NULL));
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &other)
    : AForm(other), _target(other._target) {}

RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm const &other) {
    if (this != &other) {
        AForm::operator=(other);
        _target = other._target;
    }
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::performAction() const
{
    std::cout << "making some drilling noises..." << std::endl;
    if (std::rand() % 2)
        std::cout << _target << " has been robotomized successfully." << std::endl;
    else
        std::cout << "The robotomy failed." << std::endl;
}