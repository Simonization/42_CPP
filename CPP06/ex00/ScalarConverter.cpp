#include "ScalarConverter.hpp"

// Orthodox Canonical Form - private implementations
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

// Type detection methods
bool ScalarConverter::isPseudoLiteral(const std::string& str)
{
	return (str == "nan" || str == "nanf" ||
			str == "+inf" || str == "-inf" ||
			str == "+inff" || str == "-inff" ||
			str == "inf" || str == "inff");
}

bool ScalarConverter::isChar(const std::string& str)
{
	// A char literal is a single printable character that's not a digit
	if (str.length() == 1 && !std::isdigit(str[0]))
		return true;
	return false;
}

bool ScalarConverter::isInt(const std::string& str)
{
	if (str.empty())
		return false;

	size_t i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;

	if (i == str.length())
		return false;

	for (; i < str.length(); i++)
	{
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

bool ScalarConverter::isFloat(const std::string& str)
{
	if (str.empty())
		return false;

	// Must end with 'f'
	if (str[str.length() - 1] != 'f')
		return false;

	std::string withoutF = str.substr(0, str.length() - 1);
	if (withoutF.empty())
		return false;

	size_t i = 0;
	if (withoutF[0] == '+' || withoutF[0] == '-')
		i++;

	if (i == withoutF.length())
		return false;

	bool hasDecimal = false;
	bool hasDigitBeforeDecimal = false;
	bool hasDigitAfterDecimal = false;

	for (; i < withoutF.length(); i++)
	{
		if (withoutF[i] == '.')
		{
			if (hasDecimal)
				return false;
			hasDecimal = true;
		}
		else if (std::isdigit(withoutF[i]))
		{
			if (hasDecimal)
				hasDigitAfterDecimal = true;
			else
				hasDigitBeforeDecimal = true;
		}
		else
			return false;
	}

	return hasDecimal && hasDigitBeforeDecimal && hasDigitAfterDecimal;
}

bool ScalarConverter::isDouble(const std::string& str)
{
	if (str.empty())
		return false;

	size_t i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;

	if (i == str.length())
		return false;

	bool hasDecimal = false;
	bool hasDigitBeforeDecimal = false;
	bool hasDigitAfterDecimal = false;

	for (; i < str.length(); i++)
	{
		if (str[i] == '.')
		{
			if (hasDecimal)
				return false;
			hasDecimal = true;
		}
		else if (std::isdigit(str[i]))
		{
			if (hasDecimal)
				hasDigitAfterDecimal = true;
			else
				hasDigitBeforeDecimal = true;
		}
		else
			return false;
	}

	return hasDecimal && hasDigitBeforeDecimal && hasDigitAfterDecimal;
}

// Output helpers
void ScalarConverter::printChar(double value, bool impossible)
{
	std::cout << "char: ";
	if (impossible || std::isnan(value) || std::isinf(value))
		std::cout << "impossible" << std::endl;
	else if (value < 0 || value > 127 ||
			 value != static_cast<double>(static_cast<int>(value)))
		std::cout << "impossible" << std::endl;
	else if (value < 32 || value == 127)
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
}

void ScalarConverter::printInt(double value, bool impossible)
{
	std::cout << "int: ";
	if (impossible || std::isnan(value) || std::isinf(value))
		std::cout << "impossible" << std::endl;
	else if (value < static_cast<double>(std::numeric_limits<int>::min()) ||
			 value > static_cast<double>(std::numeric_limits<int>::max()))
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(value) << std::endl;
}

void ScalarConverter::printFloat(double value, bool isNanOrInf)
{
	(void)isNanOrInf;
	std::cout << "float: ";
	float f = static_cast<float>(value);

	if (std::isnan(f))
		std::cout << "nanf" << std::endl;
	else if (std::isinf(f))
	{
		if (f > 0)
			std::cout << "+inff" << std::endl;
		else
			std::cout << "-inff" << std::endl;
	}
	else
	{
		std::cout << std::fixed << std::setprecision(1) << f << "f" << std::endl;
	}
}

void ScalarConverter::printDouble(double value, bool isNanOrInf)
{
	(void)isNanOrInf;
	std::cout << "double: ";

	if (std::isnan(value))
		std::cout << "nan" << std::endl;
	else if (std::isinf(value))
	{
		if (value > 0)
			std::cout << "+inf" << std::endl;
		else
			std::cout << "-inf" << std::endl;
	}
	else
	{
		std::cout << std::fixed << std::setprecision(1) << value << std::endl;
	}
}

// Conversion from specific types
void ScalarConverter::printFromChar(char c)
{
	double value = static_cast<double>(c);
	printChar(value, false);
	printInt(value, false);
	printFloat(value, false);
	printDouble(value, false);
}

void ScalarConverter::printFromInt(long value)
{
	bool overflow = (value < std::numeric_limits<int>::min() ||
					 value > std::numeric_limits<int>::max());

	double d = static_cast<double>(value);
	printChar(d, overflow);
	printInt(d, overflow);
	printFloat(d, false);
	printDouble(d, false);
}

void ScalarConverter::printFromFloat(float value)
{
	double d = static_cast<double>(value);
	bool isNanOrInf = std::isnan(value) || std::isinf(value);

	printChar(d, isNanOrInf);
	printInt(d, isNanOrInf);
	printFloat(d, isNanOrInf);
	printDouble(d, isNanOrInf);
}

void ScalarConverter::printFromDouble(double value)
{
	bool isNanOrInf = std::isnan(value) || std::isinf(value);

	printChar(value, isNanOrInf);
	printInt(value, isNanOrInf);
	printFloat(value, isNanOrInf);
	printDouble(value, isNanOrInf);
}

void ScalarConverter::printPseudoLiteral(const std::string& literal)
{
	double value;

	if (literal == "nan" || literal == "nanf")
		value = std::numeric_limits<double>::quiet_NaN();
	else if (literal == "+inf" || literal == "+inff" ||
			 literal == "inf" || literal == "inff")
		value = std::numeric_limits<double>::infinity();
	else
		value = -std::numeric_limits<double>::infinity();

	printFromDouble(value);
}

// Main conversion method
void ScalarConverter::convert(const std::string& literal)
{
	if (literal.empty())
	{
		std::cout << "Error: empty literal" << std::endl;
		return;
	}

	// Check for pseudo-literals first
	if (isPseudoLiteral(literal))
	{
		printPseudoLiteral(literal);
		return;
	}

	// Check for char type
	if (isChar(literal))
	{
		printFromChar(literal[0]);
		return;
	}

	// Check for int type
	if (isInt(literal))
	{
		errno = 0;
		char* endptr;
		long value = std::strtol(literal.c_str(), &endptr, 10);

		if (errno == ERANGE)
		{
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			printFloat(static_cast<double>(value), false);
			printDouble(static_cast<double>(value), false);
			return;
		}

		printFromInt(value);
		return;
	}

	// Check for float type
	if (isFloat(literal))
	{
		std::string withoutF = literal.substr(0, literal.length() - 1);
		errno = 0;
		char* endptr;
		float value = std::strtof(withoutF.c_str(), &endptr);

		printFromFloat(value);
		return;
	}

	// Check for double type
	if (isDouble(literal))
	{
		errno = 0;
		char* endptr;
		double value = std::strtod(literal.c_str(), &endptr);

		printFromDouble(value);
		return;
	}

	// Invalid input
	std::cout << "Error: invalid literal format" << std::endl;
}
