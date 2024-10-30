/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:10:20 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/30 16:36:35 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm {
    private:
        std::string _target;

    public:
        ShrubberyCreationForm(std::string const &target);
        ShrubberyCreationForm(ShrubberyCreationForm const &other);
        ShrubberyCreationForm &operator=(ShrubberyCreationForm const &other);
        ~ShrubberyCreationForm();

    protected:
        virtual void performAction() const;
};