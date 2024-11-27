/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:53:23 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/27 16:07:42 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include "MutantStack.hpp"

void testMutantStack()
{
    std::cout << "=== Testing MutantStack ===" << std::endl;
    MutantStack<int> mstack;

    // Testing basic stack operations
    mstack.push(5);
    mstack.push(17);
    std::cout << "Top: " << mstack.top() << std::endl;
    mstack.pop();
    std::cout << "Size: " << mstack.size() << std::endl;

    // Adding more elements
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    // Testing iterators
    std::cout << "Iterator test:" << std::endl;
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    while (it != ite) {
        std::cout << *it << std::endl;
        ++it;
    }

    // Testing copy constructor and assignment
    std::stack<int> s(mstack);
    std::cout << "Copied stack size: " << s.size() << std::endl;

    // Testing reverse iterators
    std::cout << "Reverse iterator test:" << std::endl;
    MutantStack<int>::reverse_iterator rit = mstack.rbegin();
    MutantStack<int>::reverse_iterator rite = mstack.rend();
    while (rit != rite) {
        std::cout << *rit << std::endl;
        ++rit;
    }
}

void testList() {
    std::cout << "\n=== Testing List (for comparison) ===" << std::endl;
    std::list<int> lst;

    // Performing same operations as MutantStack
    lst.push_back(5);
    lst.push_back(17);
    std::cout << "Back: " << lst.back() << std::endl;
    lst.pop_back();
    std::cout << "Size: " << lst.size() << std::endl;

    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0);

    std::cout << "Iterator test:" << std::endl;
    std::list<int>::iterator it = lst.begin();
    std::list<int>::iterator ite = lst.end();
    ++it;
    --it;
    while (it != ite) {
        std::cout << *it << std::endl;
        ++it;
    }
}

int main() {
    testMutantStack();
    testList();
    return 0;
} 


/*
    The key insight is that std::stack is an adapter class that uses a container (default: deque) internally.
    By accessing this->c, we get access to that underlying container and its iterators.
*/