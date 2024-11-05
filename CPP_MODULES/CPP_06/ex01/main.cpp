/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:16:03 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/05 17:27:25 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main() {
    Data originalData;
    originalData.value = 42;
    originalData.name = "Test Data";

    std::cout << "Original Data Address: " << &originalData << std::endl;
    std::cout << "Original Data Value: " << originalData.value << std::endl;
    std::cout << "Original Data Name: " << originalData.name << std::endl;

    // Serialize the Data object
    uintptr_t raw = Serializer::serialize(&originalData);
    std::cout << "Serialized Data: " << raw << std::endl;

    // Deserialize back to Data pointer
    Data* deserializedData = Serializer::deserialize(raw);
    std::cout << "Deserialized Data Address: " << deserializedData << std::endl;
    std::cout << "Deserialized Data Value: " << deserializedData->value << std::endl;
    std::cout << "Deserialized Data Name: " << deserializedData->name << std::endl;

    // Verify the pointers match
    if (deserializedData == &originalData) {
        std::cout << "Serialization/Deserialization successful!" << std::endl;
    } else {
        std::cout << "Serialization/Deserialization failed!" << std::endl;
    }

    return 0;
}


/*
   The objective of this exercise is to understand how to serialize and deserialize a pointer.
   The serialize function converts a pointer to an integer type, and the deserialize function converts an integer type to a pointer.
   The pointers match, so the serialization and deserialization were successful.
   Using reinterpret_cast instead of serialize and deserialize is not recommended because it is less safe and can lead to undefined behavior.
   The serialize and deserialize functions are more explicit and safer than reinterpret_cast.
   
*/k