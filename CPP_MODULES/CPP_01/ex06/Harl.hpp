/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:29:42 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 22:36:12 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

#include <string>                // Header file defining Harl Class with its methods

class Harl
{
private:
    void debug(void);
    void info(void);
    void warning(void);      // Methods to display messages based on the log level
    void error(void);

public:
    void filter(std::string level);  // Method to filter and display messages based on the log level
};

#endif