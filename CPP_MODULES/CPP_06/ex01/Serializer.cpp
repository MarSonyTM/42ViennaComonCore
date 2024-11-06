/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:08:58 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/06 15:26:39 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer() {}
Serializer::Serializer(const Serializer &) {}
Serializer &Serializer::operator=(const Serializer &) { return *this; }
Serializer::~Serializer() {}

uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);  // reinterpret_cast is used to convert a pointer to an integer type
}

Data* Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);      // reinterpret_cast iks used to convert an integer type to a pointer
} 

// The Serializer Class provides static methods to serialize and deserialize a pointer.