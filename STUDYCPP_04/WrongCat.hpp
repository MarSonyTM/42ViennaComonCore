/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:36:47 by marianfurni       #+#    #+#             */
/*   Updated: 2024/10/20 17:57:38 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
        
        public:
            WrongCat();
            WrongCat( const WrongCat &copy);
            WrongCat &operator=(const WrongCat &copy);
            virtual ~WrongCat();

        void makeSound() const;
        
};




#endif