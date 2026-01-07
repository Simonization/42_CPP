#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <algorithm>
# include <exception>

class Span
{
private:
	unsigned int		_maxSize;
	std::vector<int>	_numbers;

public:
	// Orthodox Canonical Form
	Span(void);
	Span(unsigned int n);
	Span(const Span& src);
	Span& operator=(const Span& other);
	~Span(void);

	// Member functions
	void addNumber(int number);
	unsigned int shortestSpan(void) const;
	unsigned int longestSpan(void) const;

	// Range insertion (template)
	template <typename Iterator>
	void addNumbers(Iterator begin, Iterator end)
	{
		while (begin != end)
		{
			this->addNumber(*begin);
			++begin;
		}
	}

	// Nested exceptions
	class SpanFullException : public std::exception
	{
	public:
		virtual const char* what(void) const throw()
		{
			return "Cannot add number: Span is full";
		}
	};

	class NoSpanException : public std::exception
	{
	public:
		virtual const char* what(void) const throw()
		{
			return "Cannot calculate span: need at least 2 numbers";
		}
	};
};

#endif
