/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:30:02 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/18 11:42:56 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

#include <string>
#include <iostream>

class Brain {

    public:
        std:: string ideas[100]; // array of 100 strings representing the ideas of the brain

        Brain();
        Brain(const Brain &copy);
        Brain &operator = (const Brain &copy);
        ~Brain();

};

#endif