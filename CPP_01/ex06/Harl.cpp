/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:31:17 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 22:16:48 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

void Harl::debug(void)
{
    std::cout << "[ DEBUG ]\nI love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I just love it!" << std::endl;
}

void Harl::info(void)
{
    std::cout << "[ INFO ]\nI cannot believe adding extra bacon cost more money. You don’t put enough! If you did I would not have to ask for it!"<< std::endl;
}

void Harl::warning(void)
{
    std::cout << "[ WARNING ]\nI think I deserve some extra bacon for free. I’ve been coming here for years and you just started working here last month." << std::endl;
}

void Harl::error(void)
{
    std::cout << "[ ERROR ]\nThis is unacceptable. I want to speak to the manager now." << std::endl;
}

void Harl::filter(std::string level)
{
    void (Harl::*complaints[4])(void) = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
    std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    int levelIndex = -1;

    for (int i = 0; i < 4; i++)
    {
        if (levels[i] == level)
        {
            levelIndex = i;
            break;
        }
    }

     switch (levelIndex)
    {
        case 0:
            (this->*complaints[0])();
           // Intentional fall-through
        case 1:
            (this->*complaints[1])();
            // Intentional fall-through
        case 2:
            (this->*complaints[2])();
             // Intentional fall-through
        case 3:
            (this->*complaints[3])();
            break;
        default:
            std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
    }
}

