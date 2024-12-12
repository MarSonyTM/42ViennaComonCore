/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:52:06 by marianfurni       #+#    #+#             */
/*   Updated: 2024/12/12 12:52:07 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>

class PmergeMe {
private:
    std::vector<int> _vec;  // First container
    std::deque<int> _deq;   // Second container
    
    // Helper methods for vector
    void mergeInsertSortVector(std::vector<int>& arr, int left, int right);
    void insertionSortVector(std::vector<int>& arr, int left, int right);
    void mergeVector(std::vector<int>& arr, int left, int mid, int right);
    
    // Helper methods for deque
    void mergeInsertSortDeque(std::deque<int>& arr, int left, int right);
    void insertionSortDeque(std::deque<int>& arr, int left, int right);
    void mergeDeque(std::deque<int>& arr, int left, int mid, int right);
    
    // Time measurement
    double getTimeInMicroseconds(clock_t start, clock_t end) const;
    
public:
    // Orthodox Canonical Form
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();
    
    // Main functionality
    void processInput(int argc, char* argv[]);
    void displayResults() const;
    
    // Exception class
    class Error : public std::runtime_error {
        public:
            explicit Error(const std::string& msg) : std::runtime_error(msg) {}
    };
}; 