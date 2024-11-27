/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:53:11 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/27 15:17:27 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

// Orthodox Canonical Form implementations
Span::Span() : _N(0) {}

Span::Span(unsigned int N) : _N(N) {}

Span::Span(const Span &other) : _N(other._N), _numbers(other._numbers) {}

Span& Span::operator=(const Span &other)
{
    if (this != &other) {
        _N = other._N;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span() {}

// Member functions
void Span::addNumber(int number)
{   //check capacity before adding
    if (_numbers.size() >= _N)  // check capacity before adding
        throw std::runtime_error("Span is full");
    _numbers.push_back(number); // add number to the container with push_back operation
}

unsigned int Span::shortestSpan() const
{
    if (_numbers.size() <= 1) // check if there are enough numbers to find span
        throw std::runtime_error("Not enough numbers to find span");

    std::vector<int> sorted = _numbers; // copy the container to a new vector
    std::sort(sorted.begin(), sorted.end()); // sort the vector

    unsigned int minSpan = static_cast<unsigned int>(sorted[1] - sorted[0]); // initialize minSpan with the first span
    for (size_t i = 2; i < sorted.size(); ++i) 
    {
        unsigned int span = static_cast<unsigned int>(sorted[i] - sorted[i-1]); // calculate the span between the current and previous number
        if (span < minSpan)
            minSpan = span; // update minSpan if the current span is smaller
    }
    return minSpan;
}

unsigned int Span::longestSpan() const
{
    if (_numbers.size() <= 1) // check if there are enough numbers to find span
        throw std::runtime_error("Not enough numbers to find span");

    // find the min and max elements in the container
    std::vector<int>::const_iterator min = std::min_element(_numbers.begin(), _numbers.end());
    std::vector<int>::const_iterator max = std::max_element(_numbers.begin(), _numbers.end());

    return static_cast<unsigned int>(*max - *min); // return the longest span
} 