/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

PhoneBook::PhoneBook() : _contactCount(0), _oldestContact(0)
{
}

PhoneBook::~PhoneBook()
{
}

std::string PhoneBook::_truncateString(const std::string &str) const
{
    if (str.length() > 10)
        return (str.substr(0, 9) + ".");
    return (str);
}

void PhoneBook::_displayContact(int index) const
{
    std::cout << "First Name: " << _contacts[index].getFirstName() << std::endl;
    std::cout << "Last Name: " << _contacts[index].getLastName() << std::endl;
    std::cout << "Nickname: " << _contacts[index].getNickname() << std::endl;
    std::cout << "Phone Number: " << _contacts[index].getPhoneNumber() << std::endl;
    std::cout << "Darkest Secret: " << _contacts[index].getDarkestSecret() << std::endl;
}

void PhoneBook::addContact()
{
    std::string input;
    int index;

    if (_contactCount < 8)
    {
        index = _contactCount;
        _contactCount++;
    }
    else
    {
        index = _oldestContact;
        _oldestContact = (_oldestContact + 1) % 8;
    }

    std::cout << "Enter first name: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        std::cout << "Contact cannot have empty fields." << std::endl;
        return;
    }
    _contacts[index].setFirstName(input);

    std::cout << "Enter last name: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        std::cout << "Contact cannot have empty fields." << std::endl;
        return;
    }
    _contacts[index].setLastName(input);

    std::cout << "Enter nickname: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        std::cout << "Contact cannot have empty fields." << std::endl;
        return;
    }
    _contacts[index].setNickname(input);

    std::cout << "Enter phone number: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        std::cout << "Contact cannot have empty fields." << std::endl;
        return;
    }
    _contacts[index].setPhoneNumber(input);

    std::cout << "Enter darkest secret: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        std::cout << "Contact cannot have empty fields." << std::endl;
        return;
    }
    _contacts[index].setDarkestSecret(input);

    std::cout << "Contact added successfully!" << std::endl;
}

void PhoneBook::searchContacts() const
{
    if (_contactCount == 0)
    {
        std::cout << "The phonebook is empty." << std::endl;
        return;
    }

    // Display header
    std::cout << std::setw(10) << std::right << "Index" << "|";
    std::cout << std::setw(10) << std::right << "First Name" << "|";
    std::cout << std::setw(10) << std::right << "Last Name" << "|";
    std::cout << std::setw(10) << std::right << "Nickname" << std::endl;

    // Display contacts
    for (int i = 0; i < _contactCount; i++)
    {
        std::cout << std::setw(10) << std::right << i << "|";
        std::cout << std::setw(10) << std::right << _truncateString(_contacts[i].getFirstName()) << "|";
        std::cout << std::setw(10) << std::right << _truncateString(_contacts[i].getLastName()) << "|";
        std::cout << std::setw(10) << std::right << _truncateString(_contacts[i].getNickname()) << std::endl;
    }

    // Ask for index
    std::cout << "Enter the index of the contact to display: ";
    std::string input;
    std::getline(std::cin, input);
    
    // Convert string to int
    std::istringstream iss(input);
    int index;
    if (!(iss >> index) || index < 0 || index >= _contactCount)
    {
        std::cout << "Invalid index." << std::endl;
        return;
    }

    _displayContact(index);
}
