/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:20:42 by marianfurni       #+#    #+#             */
/*   Updated: 2024/12/18 14:25:09 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <climits>

class RPN {
private:
    std::stack<int> _operands;  // Store numbers during calculation
    
    // Helper methods
    bool isOperator(char c) const;
    void performOperation(char op);
    bool isValidNumber(const std::string& token) const;

public:
    // Orthodox Canonical Form
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    // Main functionality
    int calculate(const std::string& expression);

    // Exception class
    class RPNError : public std::runtime_error {
        public:
            explicit RPNError(const std::string& msg) : std::runtime_error(msg) {}
    };
}; 