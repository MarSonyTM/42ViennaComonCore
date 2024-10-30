/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:55:57 by marianfurni       #+#    #+#             */
/*   Updated: 2024/10/30 21:07:58 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
    try {
        Bureaucrat bob("Bob", 3);
        ShrubberyCreationForm formA("home");

        std::cout << bob << std::endl;
        std::cout << formA << std::endl;

        bob.signForm(formA);
        std::cout << formA << std::endl;

        bob.executeForm(formA);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Bureaucrat alice("Alice", 150);
        RobotomyRequestForm formB("target");

        std::cout << alice << std::endl;
        std::cout << formB << std::endl;

        alice.signForm(formB);
        std::cout << formB << std::endl;

        alice.executeForm(formB);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Bureaucrat charlie("Charlie", 1);
        PresidentialPardonForm formC("target");

        std::cout << charlie << std::endl;
        std::cout << formC << std::endl;

        charlie.signForm(formC);
        std::cout << formC << std::endl;

        charlie.executeForm(formC);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return (0);
}