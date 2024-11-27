/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:53:27 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/27 16:10:09 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>

template<typename T>                 // template class that inherits from std::stack , gets all the methods and attributes of std::stack
class MutantStack : public std::stack<T> {
public:
    // Orthodox Canonical Form
    MutantStack() : std::stack<T>() {}
    MutantStack(const MutantStack &other) : std::stack<T>(other) {}
    MutantStack& operator=(const MutantStack &other) {
        if (this != &other)
            std::stack<T>::operator=(other);
        return *this;
    }
    ~MutantStack() {}

    // Iterator typedefs - using the underlying container's iterators
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;
    typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
    typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

    // Iterator functions
    iterator begin() { return this->c.begin(); }    // return the beginning of the underlying container
    iterator end() { return this->c.end(); }        // return the end of the underlying container
    const_iterator begin() const { return this->c.begin(); } // return the beginning of the underlying container (const)
    const_iterator end() const { return this->c.end(); }   // return the end of the underlying container (const)
    reverse_iterator rbegin() { return this->c.rbegin(); } // return the reverse beginning of the underlying container
    reverse_iterator rend() { return this->c.rend(); }     // return the reverse end of the underlying container
    const_reverse_iterator rbegin() const { return this->c.rbegin(); } // return the reverse beginning of the underlying container (const)
    const_reverse_iterator rend() const { return this->c.rend(); }     // return the reverse end of the underlying container (const)
};

/* this->c is the protected underlying container in std::stack */


/*
    The regular std::stack class is not iterable, but we can make it iterable by inheriting from it and using the underlying container's iterators.
    This way we can use the iterator functions to iterate through the stack.    
*/