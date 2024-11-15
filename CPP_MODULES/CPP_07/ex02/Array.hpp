/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:38:17 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/15 14:08:50 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <string>

template <typename T>  // Defines a template where T is a placeholder for any data type.
class Array {
    private:
        T* _elements;  // Pointer to the array of element
        unsigned int length; // Number of elements in the array
    
    public:
        // Default constructor
        Array() : _elements(NULL), length(0) {}

        // Constructor with size parameter
        Array(unsigned int n) : _elements(new T[n]()), length(n) {}

        // Copy constructor
        Array(const Array &other) : _elements(NULL), length(0){
            *this = other;
        }

        // Copy asignment operator
        Array &operator=(const Array &other) {
            if (this != &other){
                delete[] _elements; // deleting the excisting elements 
                length = other.length;
                _elements = new T[length]; // allocating new memory
                for (unsigned int i = 0; i < length; ++i) {     // copying elements from other.
                    _elements[i] = other._elements[i];
                }
            }
            return (*this);
        }

        // Destructor
        ~Array() {
            delete[] _elements; // deleting the allocated memory
        }
    
        T& operator[](unsigned int index) {
            if (index >= length) {
                throw std::out_of_range("Index out of bounds");
            }
            return (_elements[index]);
        }

        // Const subscript operator                          // provides read-only access to elements by index, trows exception if index out of bounds.
        const T& operator[](unsigned int index) const {
            if (index >= length) {
                throw std::out_of_range("Index out of bounds");
            }
            return (_elements[index]);
        }

        //Size function
        unsigned int size() const {       // returns the number of elements in the array 
            return length;
        }
};