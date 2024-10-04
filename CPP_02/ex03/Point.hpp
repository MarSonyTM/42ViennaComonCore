/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:19:29 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/04 15:22:29 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point {
private:
    Fixed x;  // x-coordinate
    Fixed y;  // y-coordinate

public:
    Point();  // Default constructor
    Point(float x, float y);  // Constructor with coordinates
    Point(const Point &copy);  // Copy constructor
    Point &operator=(const Point &copy);  // Copy assignment operator
    ~Point();  // Destructor

    Fixed getX() const;  // Getter for x
    Fixed getY() const;  // Getter for y
};

// Function to check if a point is inside a triangle
bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif
