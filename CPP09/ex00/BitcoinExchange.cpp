/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <limits>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
	: _database(src._database)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		_database = other._database;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

std::string BitcoinExchange::trim(const std::string& str) const
{
	size_t start = str.find_first_not_of(" \t\r\n");
	if (start == std::string::npos)
		return "";
	size_t end = str.find_last_not_of(" \t\r\n");
	return str.substr(start, end - start + 1);
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;

	for (size_t i = 0; i < date.length(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < 1 || month < 1 || month > 12 || day < 1)
		return false;

	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// Handle leap year
	bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if (isLeapYear)
		daysInMonth[1] = 29;

	if (day > daysInMonth[month - 1])
		return false;

	return true;
}

bool BitcoinExchange::isValidValue(const std::string& value, float& result) const
{
	std::string trimmedValue = trim(value);
	if (trimmedValue.empty())
		return false;

	char* endptr;
	double val = std::strtod(trimmedValue.c_str(), &endptr);

	// Check if the entire string was parsed
	if (*endptr != '\0')
		return false;

	// Check for negative values
	if (val < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}

	// Check for values too large
	if (val > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}

	result = static_cast<float>(val);
	return true;
}

float BitcoinExchange::getExchangeRate(const std::string& date) const
{
	std::map<std::string, float>::const_iterator it = _database.lower_bound(date);

	// If exact match found
	if (it != _database.end() && it->first == date)
		return it->second;

	// If no lower date exists (date is before all entries)
	if (it == _database.begin())
		return -1.0f;

	// Use the previous (lower) date
	--it;
	return it->second;
}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open database file");

	std::string line;
	// Skip header line
	if (std::getline(file, line))
	{
		// Verify it's a header (optional validation)
	}

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		size_t commaPos = line.find(',');
		if (commaPos == std::string::npos)
			continue;

		std::string date = trim(line.substr(0, commaPos));
		std::string rateStr = trim(line.substr(commaPos + 1));

		char* endptr;
		float rate = static_cast<float>(std::strtod(rateStr.c_str(), &endptr));
		if (*endptr != '\0')
			continue;

		_database[date] = rate;
	}

	file.close();
}

void BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	bool firstLine = true;

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		// Skip header line
		if (firstLine)
		{
			firstLine = false;
			std::string trimmedLine = trim(line);
			if (trimmedLine == "date | value")
				continue;
		}

		// Find the pipe separator
		size_t pipePos = line.find('|');
		if (pipePos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << trim(line) << std::endl;
			continue;
		}

		std::string date = trim(line.substr(0, pipePos));
		std::string valueStr = trim(line.substr(pipePos + 1));

		// Validate date
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		// Validate and parse value
		float value;
		if (!isValidValue(valueStr, value))
			continue;

		// Get exchange rate
		float rate = getExchangeRate(date);
		if (rate < 0)
		{
			std::cerr << "Error: date too early for database." << std::endl;
			continue;
		}

		// Calculate and display result
		float result = value * rate;
		std::cout << date << " => " << value << " = " << result << std::endl;
	}

	file.close();
}
