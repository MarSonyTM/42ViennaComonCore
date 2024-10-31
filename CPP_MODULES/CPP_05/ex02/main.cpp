/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:55:57 by marianfurni       #+#    #+#             */
/*   Updated: 2024/10/31 16:16:43 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
    std::srand(std::time(0));  // ensure random number generation for the robotomy , each time gets a different seed , the random number is different each time the program is run

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
 
    // Test invalid grade initialization
    try {
        Bureaucrat invalidHigh("InvalidHigh", 0);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Bureaucrat invalidLow("InvalidLow", 151);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    // Test signing a form
    try {
        Bureaucrat bob("Bob", 3);
        ShrubberyCreationForm formA("home");

        bob.signForm(formA);
        bob.signForm(formA); // Already signed
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    // Test executing a form
    try {
        Bureaucrat alice("Alice", 150);
        RobotomyRequestForm formB("target");

        alice.executeForm(formB); // Not signed
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Bureaucrat charlie("Charlie", 1);
        PresidentialPardonForm formC("target");

        charlie.signForm(formC);
        charlie.executeForm(formC); // Should succeed
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    // Test form-specific behavior
    try {
        Bureaucrat dave("Dave", 45);
        RobotomyRequestForm formD("target");

        dave.signForm(formD);
        dave.executeForm(formD); // Random success/failure
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n=== Additional Comprehensive Tests ===\n" << std::endl;
    
    // Test form execution sequence
    try {
        Bureaucrat president("President", 1);
        Bureaucrat intern("Intern", 150);
        PresidentialPardonForm form("Criminal");

        std::cout << "\nTesting unsigned form execution:" << std::endl;
        president.executeForm(form);  // Should fail - not signed

        std::cout << "\nTesting signing with insufficient grade:" << std::endl;
        intern.signForm(form);        // Should fail - grade too low

        std::cout << "\nTesting proper signing and execution sequence:" << std::endl;
        president.signForm(form);     // Should succeed
        president.executeForm(form);  // Should succeed
    } catch (std::exception &e) {
        std::cerr << "Test sequence error: " << e.what() << std::endl;
    }

    // Test copy behaviors
    std::cout << "\n=== Copy and Assignment Tests ===\n" << std::endl;
    try {
        ShrubberyCreationForm original("Garden");
        Bureaucrat supervisor("Supervisor", 1);
        
        // Sign the original
        supervisor.signForm(original);
        
        // Test copy constructor
        ShrubberyCreationForm copied(original);
        std::cout << "Original form: " << original << std::endl;
        std::cout << "Copied form: " << copied << std::endl;
        
        // Verify copied form maintains signed status
        supervisor.executeForm(copied);  // Should work if copy was proper

        // Test assignment operator
        ShrubberyCreationForm assigned("Empty");
        assigned = original;
        std::cout << "Assigned form: " << assigned << std::endl;
        supervisor.executeForm(assigned);  // Should work if assignment was proper
    } catch (std::exception &e) {
        std::cerr << "Copy test error: " << e.what() << std::endl;
    }

    // Test multiple forms simultaneously
    std::cout << "\n=== Multiple Forms Test ===\n" << std::endl;
    try {
        Bureaucrat manager("Manager", 20);
        ShrubberyCreationForm shrub("Park");
        RobotomyRequestForm robot("Patient");
        PresidentialPardonForm pardon("Prisoner");

        // Try to execute all without signing
        std::cout << "\nTrying to execute unsigned forms:" << std::endl;
        manager.executeForm(shrub);
        manager.executeForm(robot);
        manager.executeForm(pardon);

        // Sign all forms
        std::cout << "\nSigning all forms:" << std::endl;
        manager.signForm(shrub);
        manager.signForm(robot);
        manager.signForm(pardon);

        // Try to execute all (some should fail due to grade requirements)
        std::cout << "\nTrying to execute signed forms:" << std::endl;
        manager.executeForm(shrub);
        manager.executeForm(robot);
        manager.executeForm(pardon);
    } catch (std::exception &e) {
        std::cerr << "Multiple forms test error: " << e.what() << std::endl;
    }

    // Test grade boundary conditions
    std::cout << "\n=== Grade Boundary Tests ===\n" << std::endl;
    try {
        Bureaucrat exactGrade("ExactGrade", 45);  // Exact grade needed to execute RobotomyRequestForm
        RobotomyRequestForm robotForm("Test");
        
        std::cout << "Testing with exact required grade:" << std::endl;
        // Need someone with grade 72 or better to sign it first
        Bureaucrat signer("Signer", 72);
        signer.signForm(robotForm);
        exactGrade.executeForm(robotForm);

        Bureaucrat oneOff("OneOff", 46);  // One grade too low to execute
        std::cout << "\nTesting with one grade too low:" << std::endl;
        oneOff.executeForm(robotForm);
    } catch (std::exception &e) {
        std::cerr << "Boundary test error: " << e.what() << std::endl;
    }

    return (0);
}