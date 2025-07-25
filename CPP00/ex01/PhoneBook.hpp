/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:01:35 by slangero          #+#    #+#             */
/*   Updated: 2025/07/25 16:01:35 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
private:
    Contact _contacts[8];
    int _contactCount;
    int _oldestContact;

    std::string _truncateString(const std::string &str) const;
    void _displayContact(int index) const;

public:
    PhoneBook();
    ~PhoneBook();

    void addContact();
    void searchContacts() const;
};

#endif
