/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:30:17 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/10 13:12:13 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include "ClapTrap.hpp"
#include <string>

class FragTrap : virtual public ClapTrap { 
public:
    FragTrap(); 
    FragTrap(const std::string& name);
    FragTrap(const FragTrap& copy);
    FragTrap& operator = (const FragTrap& copy);
    ~FragTrap();

    void highFivesGuys(void);
};

#endif // FRAGTRAP_HPP