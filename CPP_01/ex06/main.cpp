/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:39:01 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 12:45:27 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <DEBUG> , <INFO>, <WARNING>, <ERROR>" << std::endl;
        return (1);
    }

    Harl harl;
    harl.filter(argv[1]);

    return (0);
}
