/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:54:28 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/27 15:07:07 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm> // std::find
#include <stdexcept> // std::runtime_error

template<typename T> // function can be used with different types of containers
typename T::iterator easyfind(T& container, int value)
{
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    
    if (it == container.end())
    {
        throw std::runtime_error("Value not found in container");
    }
    
    return it;
}
