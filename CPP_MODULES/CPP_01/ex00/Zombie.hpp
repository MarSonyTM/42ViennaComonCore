/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:15:38 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 20:28:07 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <string>

class Zombie{

private:
    std::string name; // private attribute to store the zombie name

public:
    Zombie(std::string name); // constructor to initialize the zombie with a name 
    ~Zombie(); // Destructor 
    void announce() const; // method to announce the zombie
};

// Function prototypes
Zombie*  newZombie(std::string name);
void randomChump(std::string name);

#endif