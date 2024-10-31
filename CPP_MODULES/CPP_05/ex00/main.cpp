/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:26:32 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/31 12:43:22 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main() {
    std::cout << "\n=== Testing normal operations ===" << std::endl;
    try {
        Bureaucrat bob("Bob", 2);
        std::cout << bob << std::endl;
        bob.incrementGrade();
        std::cout << bob << std::endl;
        bob.incrementGrade();      // this will throw an exception
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Testing lower boundary ===" << std::endl;
    try {
        Bureaucrat alice("Alice", 149);
        std::cout << alice << std::endl;
        alice.decrementGrade();
        std::cout << alice << std::endl;
        alice.decrementGrade();    // this will throw an exception
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Testing invalid grades ===" << std::endl;
    try {
        Bureaucrat invalid("Too Low", 151); // this will throw an exception
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        Bureaucrat invalid("Too High", 0); // this will throw an exception
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // New test cases to add:
    std::cout << "\n=== Testing copy constructor and assignment ===" << std::endl;
    try {
        Bureaucrat original("Original", 42);
        Bureaucrat copy(original);  // Copy constructor
        std::cout << "Original: " << original << std::endl;
        std::cout << "Copy: " << copy << std::endl;

        Bureaucrat assigned = original;  // Assignment operator
        std::cout << "Assigned: " << assigned << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Testing exact boundaries ===" << std::endl;
    try {
        Bureaucrat highest("Highest", 1);    // Should work
        Bureaucrat lowest("Lowest", 150);    // Should work
        std::cout << highest << std::endl;
        std::cout << lowest << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Testing negative grade ===" << std::endl;
    try {
        Bureaucrat negative("Negative", -5); // Should throw exception
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}