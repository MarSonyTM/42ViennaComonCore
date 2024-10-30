/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:26:32 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/30 22:08:28 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main() {
    try {
        Bureaucrat bob("Bob", 2);
        std::cout << bob << std::endl;
        bob.incrementGrade();
        std::cout << bob << std::endl;
        bob.incrementGrade();      // this will throw an exception
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Bureaucrat alice("Alice", 149);
        std::cout << alice << std::endl;
        alice.decrementGrade();
        std::cout << alice << std::endl;
        alice.decrementGrade();    // this will throw an exception
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
        std::cout << " Trying to create a Bureaucrat with a grade too low" <<std::endl;
    try {
        Bureaucrat invalid("Too Low", 151); // this will throw an exception
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
        std::cout << " Trying to create a Bureaucrat with a grade too high" <<std::endl;
     try {
        Bureaucrat invalid("Too High", 0); // this will throw an exception
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}