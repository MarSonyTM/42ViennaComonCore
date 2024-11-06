/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:16:03 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/06 13:38:37 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main() {
    // Create and initialize data
    Data originalData;
    originalData.value = 42;
    originalData.name = "Test Data";

    // Print original values
    std::cout << "Original Data:" << std::endl;
    std::cout << "Address: " << &originalData << std::endl;
    std::cout << "Value: " << originalData.value << std::endl;
    std::cout << "Name: " << originalData.name << std::endl;

    // Serialize
    uintptr_t raw = Serializer::serialize(&originalData);
    std::cout << "\nSerialized value: " << raw << std::endl;

    // Deserialize
    Data* deserializedData = Serializer::deserialize(raw);

    // Print deserialized values
    std::cout << "\nDeserialized Data:" << std::endl;
    std::cout << "Address: " << deserializedData << std::endl;
    std::cout << "Value: " << deserializedData->value << std::endl;
    std::cout << "Name: " << deserializedData->name << std::endl;

    // Verify
    if (deserializedData == &originalData) {
        std::cout << "\nPointers match - Serialization/Deserialization successful!" << std::endl;
    } else {
        std::cout << "\nPointers don't match - Serialization/Deserialization failed!" << std::endl;
    }

    // Verify data integrity
    if (deserializedData->value == originalData.value && 
        deserializedData->name == originalData.name) {
        std::cout << "Data integrity verified!" << std::endl;
    } else {
        std::cout << "Data integrity check failed!" << std::endl;
    }

    return 0;
}


/*
   The objective of this exercise is to understand how to serialize and deserialize a pointer.
   The serialize function converts a pointer to an integer type, and the deserialize function converts an integer type to a pointer.
   The pointers match, so the serialization and deserialization were successful.
   Using reinterpret_cast instead of serialize and deserialize is not recommended because it is less safe and can lead to undefined behavior.
   The serialize and deserialize functions are more explicit and safer than reinterpret_cast.
   
*/