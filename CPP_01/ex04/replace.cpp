/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:36:19 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/26 16:54:02 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

void    replace(std::string &str, const std::string &s1, const std::string &s2)
{
    size_t pos = 0;
    while ((pos = str.find(s1, pos)) != std::string::npos)
    {
        str.replace(pos, s1.length(), s2);
        pos += s2.length();
    }
}