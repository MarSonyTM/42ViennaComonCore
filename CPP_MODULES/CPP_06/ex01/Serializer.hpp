/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:05:43 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/06 15:29:00 by mafurnic         ###   ########.fr       */
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
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);
};