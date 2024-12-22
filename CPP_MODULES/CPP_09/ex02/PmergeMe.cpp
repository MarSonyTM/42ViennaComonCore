/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:52:04 by marianfurni       #+#    #+#             */
/*   Updated: 2024/12/20 12:51:17 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <limits>
#include <cctype>

// Orthodox Canonical Form
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

// Helper methods for vector
void PmergeMe::mergeInsertSortVector(std::vector<int>& arr, int left, int right) {
    if (right - left > 10) {  // Use merge sort for larger sequences
        int mid = (left + right) / 2; //mid is the middle of the array
        mergeInsertSortVector(arr, left, mid);  //sort the left half
        mergeInsertSortVector(arr, mid + 1, right); //sort the right half
        mergeVector(arr, left, mid, right); //merge the two halves
    } else {  // Use insertion sort for small sequences
        insertionSortVector(arr, left, right);
    }
} 

void PmergeMe::insertionSortVector(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) { 
        int key = arr[i];
        int j = i - 1; 
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void PmergeMe::mergeVector(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Helper methods for deque
void PmergeMe::mergeInsertSortDeque(std::deque<int>& arr, int left, int right) {
    if (right - left > 10) {  // Use merge sort for larger sequences
        int mid = (left + right) / 2;
        mergeInsertSortDeque(arr, left, mid);
        mergeInsertSortDeque(arr, mid + 1, right);
        mergeDeque(arr, left, mid, right);
    } else {  // Use insertion sort for small sequences
        insertionSortDeque(arr, left, right);
    }
}

void PmergeMe::insertionSortDeque(std::deque<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void PmergeMe::mergeDeque(std::deque<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::deque<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Time measurement
double PmergeMe::getTimeInMicroseconds(clock_t start, clock_t end) const {
    return static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

// Main functionality
void PmergeMe::processInput(int argc, char* argv[]) {
    if (argc < 2)
        throw Error("Error: no input sequence provided");
        
    // Parse and validate input
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        // Check for empty argument
        if (arg.empty())
            throw Error("Error: empty argument");
            
        // Check for non-digit characters (except spaces)
        for (size_t j = 0; j < arg.length(); ++j) {
            if (!std::isdigit(arg[j]) && !std::isspace(arg[j])) {
                throw Error("Error: invalid character in input '" + std::string(1, arg[j]) + "'");
            }
        }
        
        // Parse number
        std::istringstream iss(arg);
        long num;
        if (!(iss >> num)) {
            throw Error("Error: invalid number format in '" + arg + "'");
        }
        
        // Check for remaining characters
        std::string remaining;
        if (iss >> remaining) {
            throw Error("Error: invalid format - extra characters after number");
        }
        
        // Check number range
        if (num < 0) {
            throw Error("Error: negative number not allowed '" + arg + "'");
        }
        if (num > std::numeric_limits<int>::max()) {
            throw Error("Error: number too large '" + arg + "'");
        }
        
        _vec.push_back(static_cast<int>(num));
        _deq.push_back(static_cast<int>(num));
    }
    
    if (_vec.empty())
        throw Error("Error: empty sequence");
        
    // Display before sorting
    std::cout << "Before: ";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;
    
    // Sort using both containers and measure time
    clock_t start, end;
    
    // Only perform sort if we have more than one element
    if (_vec.size() > 1) {
        start = clock();
        mergeInsertSortVector(_vec, 0, _vec.size() - 1);
        end = clock();
    } else {
        start = end = clock();
        std::cout << "Note: Sequence contains only one element, no sorting needed." << std::endl;
    }
    double vecTime = getTimeInMicroseconds(start, end);
    
    if (_deq.size() > 1) {
        start = clock();
        mergeInsertSortDeque(_deq, 0, _deq.size() - 1);
        end = clock();
    } else {
        start = end = clock();
    }
    double deqTime = getTimeInMicroseconds(start, end);
    
    // Display results
    std::cout << "After: ";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;
    
    std::cout << "Time to process a range of " << _vec.size() 
              << " elements with std::vector : " << std::fixed 
              << std::setprecision(5) << vecTime << " us" << std::endl;
              
    std::cout << "Time to process a range of " << _deq.size() 
              << " elements with std::deque : " << std::fixed 
              << std::setprecision(5) << deqTime << " us" << std::endl;
} 