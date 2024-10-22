/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:23:43 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/07 15:07:51 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include <iostream>

int main() {
    
    Point a(0.0f, 0.0f);  // Triangle vertex A
    Point b(5.0f, 0.0f);  // Triangle vertex B
    Point c(0.0f, 5.0f);  // Triangle vertex C

    Point pointInside(1.0f, 1.0f);  // Point inside triangle
    Point pointOutside(6.0f, 6.0f);  // Point outside triangle
    Point pointOnEdge(0.0f, 0.0f);  // Point on edge of triangle
    Point Test(1.2f, 1.0f);   // test to mess around with

    // Test if points are inside the triangle
    std::cout << "Is point (1,1) inside triangle? "   << (bsp(a, b, c, pointInside) ? "Yes" : "No") << std::endl;
    std::cout << "Is point (6,6) inside triangle? "   << (bsp(a, b, c, pointOutside) ? "Yes" : "No") << std::endl;
    std::cout << "Is point (0,0) inside triangle? "   << (bsp(a, b, c, pointOnEdge) ? "Yes" : "No") << std::endl;
    std::cout << "Is point (1.2,0) inside triangle? " << (bsp(a, b, c, Test) ? "Yes" : "No") << std::endl;
   
    return (0);
}
