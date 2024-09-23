/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:51:32 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/23 14:57:43 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
        return (0);
    }
    for(int i = 1; i < ac; i++)
    {
        for(int j = 0; av[i][j]; j++)
        {
            std::cout << (char)std::toupper(av[i][j]);
        }
        std::cout << " "; 
    }
    std::cout << std::endl;
    return (0);
}
