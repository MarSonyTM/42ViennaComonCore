/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:53:23 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/28 11:58:59 by marianfurni      ###   ########.fr       */
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
    std::cout << "Top: " << mstack.top() << std::endl; // display the top element   
    mstack.pop();
    std::cout << "Size: " << mstack.size() << std::endl; // display the size of the stack

    // Adding more elements
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    // Testing iterators
    std::cout << "Iterator test:" << std::endl;
    MutantStack<int>::iterator it = mstack.begin(); // get the beginning of the stack   
    MutantStack<int>::iterator ite = mstack.end(); // get the end of the stack
    ++it; // increment the iterator
    --it; // decrement the iterator
    while (it != ite) {
        std::cout << *it << std::endl; // display the element
        ++it; // increment the iterator
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
    lst.push_back(5); // add element to the end of the list
    lst.push_back(17); // add element to the end of the list
    std::cout << "Back: " << lst.back() << std::endl; // display the last element
    lst.pop_back(); // remove the last element
    std::cout << "Size: " << lst.size() << std::endl; // display the size of the list

    lst.push_back(3); // add element to the end of the list
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0); 

    std::cout << "Iterator test:" << std::endl;
    std::list<int>::iterator it = lst.begin(); // get the beginning of the list
    std::list<int>::iterator ite = lst.end(); // get the end of the list    
    ++it; // increment the iterator
    --it; // decrement the iterator
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
}

int main()
{
    testMutantStack(); // test the MutantStack
    testList(); // test the List
    return 0;
} 


/*
    The key insight is that std::stack is an adapter class that uses a container (default: deque) internally.
    By accessing this->c, we get access to that underlying container and its iterators.
*/