/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:18:19 by marianfurni       #+#    #+#             */
/*   Updated: 2024/11/06 13:18:20 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Base {
public:
    virtual ~Base();
};

class A : public Base {};
class B : public Base {};
class C : public Base {};

Base* generate(void);
void identify(Base* p);
void identify(Base& p); 