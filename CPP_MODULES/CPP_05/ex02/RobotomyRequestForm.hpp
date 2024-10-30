/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:22:21 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/30 16:40:29 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include "AForm.hpp"
#include <cstdlib>
#include <ctime>

class RobotomyRequestForm : public AForm {
    private:
        std::string _target;

    public:
        RobotomyRequestForm(std::string const &target);
        RobotomyRequestForm(RobotomyRequestForm const &other);
        RobotomyRequestForm &operator=(RobotomyRequestForm const &other);
        ~RobotomyRequestForm();

        virtual void performAction() const;
};