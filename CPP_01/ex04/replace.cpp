/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:36:19 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 21:43:29 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

void    replace(std::string &str, const std::string &s1, const std::string &s2)
{
    size_t pos = 0; //initialize the position to 0 to keep track of the position of the substring
    while ((pos = str.find(s1, pos)) != std::string::npos) //find the position of the substring in the string
    {
        str.replace(pos, s1.length(), s2); 
        pos += s2.length();  //increment the position by the length of the substring to avoid infinite loop
    }
}