/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:16:03 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/05 13:18:17 by mafurnic         ###   ########.fr       */
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
    unsigned long raw = Serializer::serialize(&originalData);
    std::cout << "Serialized Data: " << raw << std::endl;

    // Deserialize the raw value back to a Data pointer
    Data* deserializedData = Serializer::deserialize(raw);
    std::cout << "Deserialized Data Address: " << deserializedData << std::endl;
    std::cout << "Deserialized Data Value: " << deserializedData->value << std::endl;
    std::cout << "Deserialized Data Name: " << deserializedData->name << std::endl;

    // Ensure the deserialized pointer compares equal to the original pointer
    if (deserializedData == &originalData) {
        std::cout << "Deserialization successful: Pointers match." << std::endl;
    } else {
        std::cout << "Deserialization failed: Pointers do not match." << std::endl;
    }

    return 0;
}