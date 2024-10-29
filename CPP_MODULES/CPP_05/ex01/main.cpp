/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:26:32 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/29 14:00:20 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    try {
        Bureaucrat bob("Bob", 2);
        Form formA("Form A", 1, 1);
        Form formB("Form B", 3, 3);

        std::cout << bob << std::endl;
        std::cout << formA << std::endl;
        std::cout << formB << std::endl;

        std::cout << "Bob is attempting to sign forms A and B" << std::endl;
        bob.signForm(formA);
        bob.signForm(formB);

        std::cout << formA << std::endl;
        std::cout << formB << std::endl;   
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
    