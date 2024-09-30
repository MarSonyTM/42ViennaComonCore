/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:39:01 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 14:31:15 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <DEBUG> , <INFO>, <WARNING>, <ERROR>" << std::endl;
        return (1);
    }

    Harl harl;
    harl.filter(argv[1]);

    return (0);
}

/*
        The Goal of this excercise if to create a programm that filters
        and displays messages from a character named Harl based on a specific log level.
        The prgramm should display mesagges staring from the specified log level up to the highest level (ERROR).
*/