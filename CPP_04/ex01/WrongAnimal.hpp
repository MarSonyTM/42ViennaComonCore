/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:01:16 by mafurnic          #+#    #+#             */
/*   Updated: 2024/10/15 12:11:44 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <string>
#include <iostream>

class WrongAnimal 
{
    protected: 
        std::string type;

    public:
        WrongAnimal();
        WrongAnimal(const WrongAnimal &copy);
        WrongAnimal &operator=(const WrongAnimal &copy);
        virtual ~WrongAnimal();

    virtual void makeSound() const;
    std::string getType() const;
};

#endif

/*
        WrongAnimal class is similar to Animal class , but without virtual funtions.
        This demonstartes what happends when polymorphism is not used.The function can't
        be overridden and the call will be for makeSound always the base one.
*/