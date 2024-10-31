/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:26:32 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/31 13:39:43 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    // Test 1: Basic functionality
    try {
        std::cout << "\n=== Test 1: Basic Functionality ===\n";
        Bureaucrat bob("Bob", 3);
        Form formA("FormA", 3, 5);
        std::cout << bob << std::endl;
        std::cout << formA << std::endl;
        bob.signForm(formA);
        std::cout << formA << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Test 1 failed: " << e.what() << std::endl;
    }

    // Test 2: Attempt to sign already signed form
    try {
        std::cout << "\n=== Test 2: Already Signed Form ===\n";
        Bureaucrat john("John", 1);
        Form formB("FormB", 1, 1);
        john.signForm(formB);
        std::cout << "First signing successful\n";
        john.signForm(formB); // Trying to sign again
    } catch (std::exception &e) {
        std::cerr << "Test 2 failed: " << e.what() << std::endl;
    }

    // Test 3: Grade boundaries
    try {
        std::cout << "\n=== Test 3: Grade Boundaries ===\n";
        Bureaucrat low("LowLevel", 150);
        Form highForm("HighForm", 1, 1);
        low.signForm(highForm); // Should fail with GradeTooLowException
    } catch (std::exception &e) {
        std::cerr << "Test 3 failed: " << e.what() << std::endl;
    }

    // Test 4: Form creation with invalid grades
    try {
        std::cout << "\n=== Test 4: Invalid Form Creation ===\n";
        Form invalid1("Invalid1", 0, 50);    // Too high
    } catch (std::exception &e) {
        std::cerr << "Test 4.1: " << e.what() << std::endl;
    }
    try {
        Form invalid2("Invalid2", 50, 151);  // Too low
    } catch (std::exception &e) {
        std::cerr << "Test 4.2: " << e.what() << std::endl;
    }

    // Test 5: Copy constructor and assignment operator
    try {
        std::cout << "\n=== Test 5: Copy Tests ===\n";
        Form original("Original", 50, 50);
        Bureaucrat boss("Boss", 1);
        boss.signForm(original);
        
        // Added better assignment operator test
        Form assigned("AssignedForm", 75, 75);  // Different initial values
        std::cout << "Before assignment: " << assigned << std::endl;
        assigned = original;
        std::cout << "After assignment: " << assigned << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Test 5 failed: " << e.what() << std::endl;
    }

    return 0;
}
    