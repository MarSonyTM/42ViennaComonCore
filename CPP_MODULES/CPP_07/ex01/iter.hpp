/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:10:11 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/15 14:57:21 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//Can modify elements (non-const version)
template <typename T>
void iter(T *array, int length, void(*func)(T&))
{
    if (!array || length <= 0) // Check if array is null or empty
        return;
    for (int i = 0; i < length; i++)    // Iterate through the array
        func(array[i]);                  // Apply the function to each element
}

// Cannot modify elements (const version), can only read from them
template <typename T>
void iter(const T *array, int length, void(*func)(const T&))
{
    if (!array || length <= 0) // Check if array is null or empty
        return;
    for (int i = 0; i < length; i++)    // Iterate through the array
        func(array[i]);                  // Apply the function to each element
}