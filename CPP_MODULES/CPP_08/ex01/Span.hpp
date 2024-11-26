/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:42:54 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/26 17:53:14 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

class Span {
private:
    unsigned int        _N;
    std::vector<int>   _numbers;

public:
    // Orthodox Canonical Form
    Span();
    Span(unsigned int N);
    Span(const Span& other);
    Span& operator=(const Span& other);
    ~Span();

    // Member functions
    void addNumber(int number);
    unsigned int shortestSpan() const;
    unsigned int longestSpan() const;

    // Bonus: Add range of numbers
    template<typename Iterator>
    void addRange(Iterator begin, Iterator end) {
        while (begin != end) {
            addNumber(*begin);
            ++begin;
        }
    }
};

#endif 