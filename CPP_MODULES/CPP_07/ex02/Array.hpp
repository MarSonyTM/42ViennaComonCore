/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:38:17 by mafurnic          #+#    #+#             */
/*   Updated: 2024/11/15 13:11:51 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <string>

template <typename T>
class Array {
    private:
        T* _elements;
        unsigned int length;
    
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
                delete[] _elements;
                length = other.length;
                _elements = new T[length];
                for (unsigned int i = 0; i < length; ++i) {
                    _elements[i] = other._elements[i];
                }
            }
            return (*this);
        }

        // Destructor
        ~Array() {
            delete[] _elements;
        }
    
        T& operator[](unsigned int index) {
            if (index >= length) {
                throw std::out_of_range("Index out of bounds");
            }
            return (_elements[index]);
        }

        // Const subscript operator
        const T& operator[](unsigned int index) const {
            if (index >= length) {
                throw std::out_of_range("Index out of bounds");
            }
            return (_elements[index]);
        }

        //Size function
        unsigned int size() const {
            return length;
        }
};