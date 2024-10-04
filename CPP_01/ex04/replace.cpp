/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:36:19 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/01 12:21:30 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

void    replace(std::string &str, const std::string &s1, const std::string &s2)
{
    size_t pos = 0; //initialize the position to 0 to keep track of the position of the substring
    while ((pos = str.find(s1, pos)) != std::string::npos) //find the position of the substring in the string
    {                                                
        str.replace(pos, s1.length(), s2); // replace the substring with the new substring
        pos += s2.length();  //increment the position by the length of the substring to avoid infinite loop
    }
}