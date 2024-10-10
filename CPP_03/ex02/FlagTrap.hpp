/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlagTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:30:17 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/10 12:03:31 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGTRAP_HPP
# define FLAGTRAP_HPP

#include "ClapTrap.hpp"
#include <string>

class FlagTrap : public ClapTrap { 
public:
    FlagTrap(); 
    FlagTrap(const std::string& name);
    FlagTrap(const FlagTrap& copy);
    FlagTrap& operator = (const FlagTrap& copy);
    ~FlagTrap();

    void highFivesGuys(void);
};

#endif // FLAGTRAP_HPP