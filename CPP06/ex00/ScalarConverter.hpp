/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <cerrno>
#include <iomanip>

class ScalarConverter
{
public:
	static void convert(const std::string& literal);

private:
	// Orthodox Canonical Form - private to prevent instantiation
	ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter& operator=(const ScalarConverter& other);
	~ScalarConverter();

	// Type detection helpers
	static bool isChar(const std::string& str);
	static bool isInt(const std::string& str);
	static bool isFloat(const std::string& str);
	static bool isDouble(const std::string& str);
	static bool isPseudoLiteral(const std::string& str);

	// Conversion and printing helpers
	static void printFromChar(char c);
	static void printFromInt(long value);
	static void printFromFloat(float value);
	static void printFromDouble(double value);
	static void printPseudoLiteral(const std::string& literal);

	// Output helpers
	static void printChar(double value, bool impossible);
	static void printInt(double value, bool impossible);
	static void printFloat(double value, bool isNanOrInf);
	static void printDouble(double value, bool isNanOrInf);
};

#endif
