/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:26:32 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/30 20:11:58 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    try {
        Bureaucrat bob("Bob", 3);
        Form formA("Form", 3, 5);

        std::cout << bob << std::endl;
        std::cout << formA << std::endl;

        bob.signForm(formA);
        std::cout << formA << std::endl;

        bob.decrementGrade(); // GradeTooLowException
        bob.signForm(formA);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Bureaucrat alice("Alice", 150);
        Form formB("Form", 150, 150);

        std::cout << alice << std::endl;
        std::cout << formB << std::endl;

        alice.signForm(formB);
        std::cout << formB << std::endl;

        alice.decrementGrade(); // GradeTooLowException
        alice.signForm(formB);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

     try {
        Bureaucrat charlie("Charlie", 1);
        Form formC("FormC", 1, 1);

        std::cout << charlie << std::endl;
        std::cout << formC << std::endl;

        charlie.signForm(formC);
        std::cout << formC << std::endl;

        charlie.incrementGrade(); // GradeTooHighException
        charlie.signForm(formC);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Form invalidForm("Invalid Form", 0, 0); // GradeTooHighException
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Form invalidForm("Invalid Form", 151, 151); // GradeTooLowException
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
    