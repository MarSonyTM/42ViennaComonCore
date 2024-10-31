/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:39:00 by marianfurni       #+#    #+#             */
/*   Updated: 2024/10/31 14:56:25 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"
#include <cstdlib> 
#include <ctime>

class RobotomyRequestForm : public AForm
{
    protected:
        void performAction() const;
    private:
        std::string _target;
    public:
        RobotomyRequestForm(std::string const &target);
        RobotomyRequestForm(const RobotomyRequestForm &copy);
        RobotomyRequestForm &operator=(const RobotomyRequestForm &copy);
        virtual ~RobotomyRequestForm();
};