/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:54:28 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/27 12:22:27 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm> // std::find
#include <stdexcept> // std::runtime_error

template<typename T> // function can be used with different types of containers
typename T::iterator easyfind(T& container, int value)
{
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    
    if (it == container.end()) {
        throw std::runtime_error("Value not found in container");
    }
    
    return it;
}
