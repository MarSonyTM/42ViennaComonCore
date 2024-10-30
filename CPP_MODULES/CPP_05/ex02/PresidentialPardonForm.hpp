/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:33:30 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/30 16:42:30 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
    private:
            std::string _target;

    public:
            PresidentialPardonForm(std::string const &target);
            PresidentialPardonForm(PresidentialPardonForm const &other);
            PresidentialPardonForm &operator = (PresidentialPardonForm const &other);
            ~PresidentialPardonForm();

            virtual void performAction() const;
};