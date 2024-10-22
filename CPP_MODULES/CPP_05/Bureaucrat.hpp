/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:45:18 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/22 12:16:04 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Bureaucrat {
    
    private:
        std::string const _name;
        int _grade;
    
    public:
        Bureaucrat(std::string const &name, int grade);
        
 
    
              
};
