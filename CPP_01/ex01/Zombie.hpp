/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:21:40 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/30 21:15:06 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <string>

class Zombie {
private:
    std::string name; //  private attribute to store the zombie name

public:
    Zombie(); // default constructor to initialize the zombie with an empty name
    Zombie(::std::string name); // parameterized constructor to initialize the zombie with a name
    ~Zombie(); // Destructor to handle clean up
    
    void announce(); // method to announce the zombie
};

// Function to create a horde of zombies
Zombie* zombieHorde(int N, std::string name);


#endif
