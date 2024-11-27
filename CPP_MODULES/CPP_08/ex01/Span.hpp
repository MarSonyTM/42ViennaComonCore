/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:42:54 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/27 14:11:12 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

class Span {
private:
    unsigned int        _N;       // Maximum number of elements
    std::vector<int>   _numbers; // Container to store numbers

public:
    // Orthodox Canonical Form
    Span();
    Span(unsigned int N); // Constructor with maximum number of elements
    Span(const Span& other);
    Span& operator=(const Span& other);
    ~Span();

    // Member functions
    void addNumber(int number); // Add number to container
    unsigned int shortestSpan() const; // Find shortest span between two numbers
    unsigned int longestSpan() const; // Find longest span between two numbers

    // Bonus: Add range of numbers
    template<typename Iterator>
    void addRange(Iterator begin, Iterator end) {
    if (std::distance(begin, end) + _numbers.size() > _N) {
        throw std::runtime_error("Span will be full");
    }
    _numbers.insert(_numbers.end(), begin, end);
}
};

#endif 