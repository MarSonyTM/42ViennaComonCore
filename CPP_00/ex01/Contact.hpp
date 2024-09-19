/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:47:21 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/19 14:44:23 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
private:
    std::string first_name;
    std::string last_name;
    std::string nickname;
    std::string phone_number;
    std::string darkest_secret;

    bool is_valid_phone_number(const std::string &phone_number) const;

public:
    void setFirstName(const std::string &first_name);
    void setLastName(const std::string &last_name);
    void setNickname(const std::string &nickname);
    void setPhoneNumber(const std::string &phone_number);
    void setDarkestSecret(const std::string &darkest_secret);

    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const std::string &getNickname() const;
    const std::string &getPhoneNumber() const;
    const std::string &getDarkestSecret() const;

    void set_contact_info();
    void display_summary(int index) const;
    void display_full_info() const;
};

#endif // CONTACT_HPP