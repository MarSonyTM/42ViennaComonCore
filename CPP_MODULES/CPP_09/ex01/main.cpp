/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:30:50 by marianfurni       #+#    #+#             */
/*   Updated: 2024/12/18 14:12:39 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Error: wrong number of arguments" << std::endl;
        return 1;
    }

    try {
        RPN calculator;
        int result = calculator.calculate(argv[1]);
        std::cout << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
} 