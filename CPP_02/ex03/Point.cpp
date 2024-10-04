/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:20:42 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/04 15:26:03 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

// Default constructor
Point::Point() : x(0), y(0) {}

// Constructor with coordinates
Point::Point(float xCoord, float yCoord) : x(xCoord), y(yCoord) {}

// Copy constructor
Point::Point(const Point &copy) : x(copy.getX()), y(copy.getY()) {}

// Copy assignment operator
Point &Point::operator=(const Point &copy) {
    if (this != &copy) {
        this->x = copy.getX();
        this->y = copy.getY();
    }
    return *this;
}

// Destructor
Point::~Point() {}

// Getter for x
Fixed Point::getX() const {
    return x;
}

// Getter for y
Fixed Point::getY() const {
    return y;
}
