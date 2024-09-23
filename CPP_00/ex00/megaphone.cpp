/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:51:32 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/23 22:20:14 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream> // std::cout, std::endl
#include <cctype> // std::toupper

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
            std::cout << std::toupper(av[i][j]);
        }
        std::cout << " "; 
    }
    std::cout << std::endl;
    return (0);
}
