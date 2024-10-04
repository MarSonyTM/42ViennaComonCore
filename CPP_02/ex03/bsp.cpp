/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:26:11 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/04 15:27:32 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

// Function to check if a point is inside a triangle
bool bsp(Point const a, Point const b, Point const c, Point const point) {
    // Calculate areas using the cross product method
    float areaABC = (b.getX() - a.getX()).toFloat() * (c.getY() - a.getY()).toFloat() - (c.getX() - a.getX()).toFloat() * (b.getY() - a.getY()).toFloat();
    float areaABP = (b.getX() - a.getX()).toFloat() * (point.getY() - a.getY()).toFloat() - (point.getX() - a.getX()).toFloat() * (b.getY() - a.getY()).toFloat();
    float areaBCP = (c.getX() - b.getX()).toFloat() * (point.getY() - b.getY()).toFloat() - (point.getX() - b.getX()).toFloat() * (c.getY() - b.getY()).toFloat();

    // Check if the point is inside the triangle
    return (areaABC > 0 && areaABP > 0 && areaBCP > 0) || (areaABC < 0 && areaABP < 0 && areaBCP < 0);
}
