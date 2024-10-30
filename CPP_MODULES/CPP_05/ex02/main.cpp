/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:48:15 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/30 17:05:08 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
    try {
        Bureaucrat bob("Bob", 2);
        ShrubberyCreationForm shrubbery("home");
        RobotomyRequestForm robotomy("Alice");
        PresidentialPardonForm pardon("Marvin");

        std::cout << bob << std::endl;
        std::cout << shrubbery << std::endl;
        std::cout << robotomy << std::endl;
        std::cout << pardon << std::endl;

        bob.signForm(shrubbery);
        bob.signForm(robotomy);
        bob.signForm(pardon);

        bob.executeForm(shrubbery);
        bob.executeForm(robotomy);
        bob.executeForm(pardon);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}