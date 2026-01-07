#include "Span.hpp"

// Default constructor
Span::Span(void) : _maxSize(0)
{
}

// Parameterized constructor
Span::Span(unsigned int n) : _maxSize(n)
{
	this->_numbers.reserve(n);
}

// Copy constructor
Span::Span(const Span& src) : _maxSize(src._maxSize), _numbers(src._numbers)
{
}

// Assignment operator
Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		this->_maxSize = other._maxSize;
		this->_numbers = other._numbers;
	}
	return *this;
}

// Destructor
Span::~Span(void)
{
}

// Add a single number
void Span::addNumber(int number)
{
	if (this->_numbers.size() >= this->_maxSize)
		throw SpanFullException();
	this->_numbers.push_back(number);
}

// Find the shortest span (smallest difference between any two numbers)
unsigned int Span::shortestSpan(void) const
{
	if (this->_numbers.size() < 2)
		throw NoSpanException();

	std::vector<int> sorted = this->_numbers;
	std::sort(sorted.begin(), sorted.end());

	unsigned int minSpan = static_cast<unsigned int>(sorted[1] - sorted[0]);
	for (size_t i = 2; i < sorted.size(); i++)
	{
		unsigned int diff = static_cast<unsigned int>(sorted[i] - sorted[i - 1]);
		if (diff < minSpan)
			minSpan = diff;
	}
	return minSpan;
}

// Find the longest span (largest difference between any two numbers)
unsigned int Span::longestSpan(void) const
{
	if (this->_numbers.size() < 2)
		throw NoSpanException();

	int min = *std::min_element(this->_numbers.begin(), this->_numbers.end());
	int max = *std::max_element(this->_numbers.begin(), this->_numbers.end());
	return static_cast<unsigned int>(max - min);
}
