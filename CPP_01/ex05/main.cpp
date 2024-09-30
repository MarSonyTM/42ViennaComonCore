/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:08:34 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 21:54:55 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main()
{
    Harl harl; // Creata a instance of the Harl class

    harl.complain("DEBUG");
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");
    harl.complain("UNKNOWN");

    return (0);
}

/*
    The Goal of this exercise is to create a Harl Class that can output different messages
    based on a given log level. The log levels are DEBUG, INFO, WARNING and ERROR.
    The Harl class should use pointers to member functions to call the apporproate function based on the log level.
    avoiding the use of series of if/else statements.

*/