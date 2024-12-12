/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:20:47 by marianfurni       #+#    #+#             */
/*   Updated: 2024/12/12 12:20:48 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// Orthodox Canonical Form
RPN::RPN() {}

RPN::RPN(const RPN& other) : _operands(other._operands) {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        _operands = other._operands;
    }
    return *this;
}

RPN::~RPN() {}

// Helper methods
bool RPN::isOperator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool RPN::isValidNumber(const std::string& token) const {
    if (token.length() != 1) return false;
    return token[0] >= '0' && token[0] <= '9';
}

void RPN::performOperation(char op) {
    if (_operands.size() < 2) {
        throw RPNError("Error: not enough operands");
    }

    int b = _operands.top(); _operands.pop();
    int a = _operands.top(); _operands.pop();

    switch (op) {
        case '+':
            _operands.push(a + b);
            break;
        case '-':
            _operands.push(a - b);
            break;
        case '*':
            _operands.push(a * b);
            break;
        case '/':
            if (b == 0) throw RPNError("Error: division by zero");
            _operands.push(a / b);
            break;
    }
}

// Main functionality
int RPN::calculate(const std::string& expression) {
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (isValidNumber(token)) {
            int num = token[0] - '0';
            if (num >= 10) {
                throw RPNError("Error: number >= 10");
            }
            _operands.push(num);
        }
        else if (token.length() == 1 && isOperator(token[0])) {
            performOperation(token[0]);
        }
        else {
            throw RPNError("Error: invalid token");
        }
    }

    if (_operands.size() != 1) {
        throw RPNError("Error: invalid expression");
    }

    return _operands.top();
} 