/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
private:
	std::map<std::string, float> _database;

	bool		isValidDate(const std::string& date) const;
	bool		isValidValue(const std::string& value, float& result) const;
	float		getExchangeRate(const std::string& date) const;
	std::string	trim(const std::string& str) const;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& src);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void	loadDatabase(const std::string& filename);
	void	processInput(const std::string& filename);
};

#endif
