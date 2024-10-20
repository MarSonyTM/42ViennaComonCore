/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:25:57 by marianfurni       #+#    #+#             */
/*   Updated: 2024/10/20 18:09:07 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <iostream>
#include <string>

class WrongAnimal {
    protected:
            std::string type;
    
    public:
            WrongAnimal();
            WrongAnimal( const WrongAnimal &copy );
            WrongAnimal &operator = (const WrongAnimal &copy);
            virtual ~WrongAnimal();

    void makeSound() const;
    std::string getType() const;
};


#endif
