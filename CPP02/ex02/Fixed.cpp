#include "Fixed.hpp"
#include <cmath>

// Orthodox Canonical Form
Fixed::Fixed(void) : _rawBits(0)
{
	// std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &src)
{
	// std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

Fixed &Fixed::operator=(const Fixed &rhs)
{
	// std::cout << "Copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->_rawBits = rhs.getRawBits();
	return *this;
}

Fixed::~Fixed(void)
{
	// std::cout << "Destructor called" << std::endl;
}

// Additional constructors
Fixed::Fixed(const int n) : _rawBits(n << _fractionalBits)
{
	// std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float n) : _rawBits(roundf(n * (1 << _fractionalBits)))
{
	// std::cout << "Float constructor called" << std::endl;
}

// Getters and setters
int Fixed::getRawBits(void) const
{
	return this->_rawBits;
}

void Fixed::setRawBits(int const raw)
{
	this->_rawBits = raw;
}

// Conversion functions
float Fixed::toFloat(void) const
{
	return static_cast<float>(this->_rawBits) / (1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
	return this->_rawBits >> _fractionalBits;
}

// Comparison operators
bool Fixed::operator>(const Fixed &rhs) const
{
	return this->_rawBits > rhs._rawBits;
}

bool Fixed::operator<(const Fixed &rhs) const
{
	return this->_rawBits < rhs._rawBits;
}

bool Fixed::operator>=(const Fixed &rhs) const
{
	return this->_rawBits >= rhs._rawBits;
}

bool Fixed::operator<=(const Fixed &rhs) const
{
	return this->_rawBits <= rhs._rawBits;
}

bool Fixed::operator==(const Fixed &rhs) const
{
	return this->_rawBits == rhs._rawBits;
}

bool Fixed::operator!=(const Fixed &rhs) const
{
	return this->_rawBits != rhs._rawBits;
}

// Arithmetic operators
Fixed Fixed::operator+(const Fixed &rhs) const
{
	Fixed result;
	result.setRawBits(this->_rawBits + rhs._rawBits);
	return result;
}

Fixed Fixed::operator-(const Fixed &rhs) const
{
	Fixed result;
	result.setRawBits(this->_rawBits - rhs._rawBits);
	return result;
}

Fixed Fixed::operator*(const Fixed &rhs) const
{
	Fixed result;
	long long temp = static_cast<long long>(this->_rawBits) * static_cast<long long>(rhs._rawBits);
	result.setRawBits(static_cast<int>(temp >> _fractionalBits));
	return result;
}

Fixed Fixed::operator/(const Fixed &rhs) const
{
	Fixed result;
	long long temp = (static_cast<long long>(this->_rawBits) << _fractionalBits) / rhs._rawBits;
	result.setRawBits(static_cast<int>(temp));
	return result;
}

// Increment/Decrement operators
Fixed &Fixed::operator++(void)	// Pre-increment
{
	this->_rawBits++;
	return *this;
}

Fixed Fixed::operator++(int)	// Post-increment
{
	Fixed temp(*this);
	this->_rawBits++;
	return temp;
}

Fixed &Fixed::operator--(void)	// Pre-decrement
{
	this->_rawBits--;
	return *this;
}

Fixed Fixed::operator--(int)	// Post-decrement
{
	Fixed temp(*this);
	this->_rawBits--;
	return temp;
}

// Static member functions
Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return (a < b) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a < b) ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return (a > b) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a > b) ? a : b;
}

// Stream insertion operator
std::ostream &operator<<(std::ostream &o, const Fixed &rhs)
{
	o << rhs.toFloat();
	return o;
}