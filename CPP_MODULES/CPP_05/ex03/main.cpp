/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:23:00 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/31 16:23:14 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include <string>
#include <iostream>

int main() {
    std::cout << "\n=== Basic Form Creation Tests ===\n" << std::endl;
    try {
        Intern someRandomIntern;
        Bureaucrat boss("Boss", 1);
        AForm* rrf;

        // Test successful form creation
        rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        boss.signForm(*rrf);
        boss.executeForm(*rrf);
        delete rrf;

        // Test invalid form name
        std::cout << "\nTesting invalid form name:" << std::endl;
        AForm* invalid = someRandomIntern.makeForm("invalid form", "target");
        delete invalid;  // Won't be reached due to exception
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n=== Memory Management Test ===\n" << std::endl;
    try {
        Intern intern;
        // Create and immediately delete forms
        for (int i = 0; i < 3; i++) {
            AForm* form = intern.makeForm("robotomy request", "Test Subject " + std::to_string(i));
            delete form;
        }
        std::cout << "Memory management test completed successfully" << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return (0);
}