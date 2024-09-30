/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:08:34 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 12:23:48 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main()
{
    Harl harl;

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