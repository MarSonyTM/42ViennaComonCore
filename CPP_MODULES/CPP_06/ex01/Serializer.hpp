/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:05:43 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/13 13:04:27 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <stdint.h> // For uintptr_t

struct Data {      // This Data Structure is used to test the serialization and deserialization of a pointer
    int value;
    std::string name;
};

class Serializer {
    private:
        Serializer();
        Serializer(const Serializer &);
        Serializer &operator=(const Serializer &);
        ~Serializer();

    public:
        static uintptr_t serialize(Data* ptr); // serialize the pointer to an integer type
        static Data* deserialize(uintptr_t raw); // deserialize the integer type to a pointer
};