#include "RPN.hpp"

// Default constructor
RPN::RPN()
{
}

// Copy constructor
RPN::RPN(const RPN& src)
{
	_stack = src._stack;
}

// Copy assignment operator
RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		_stack = other._stack;
	}
	return *this;
}

// Destructor
RPN::~RPN()
{
}

// Check if character is an operator
bool RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Check if character is a digit
bool RPN::isDigit(char c) const
{
	return (c >= '0' && c <= '9');
}

// Perform arithmetic operation
double RPN::performOperation(double a, double b, char op) const
{
	switch (op)
	{
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if (b == 0)
				throw std::runtime_error("Division by zero");
			return a / b;
		default:
			throw std::runtime_error("Invalid operator");
	}
}

// Evaluate RPN expression
double RPN::evaluate(const std::string& expression)
{
	// Clear stack before evaluation
	while (!_stack.empty())
		_stack.pop();

	if (expression.empty())
		throw std::runtime_error("Empty expression");

	for (size_t i = 0; i < expression.length(); ++i)
	{
		char c = expression[i];

		// Skip whitespace
		if (c == ' ' || c == '\t')
			continue;

		// Check for invalid characters (brackets, etc.)
		if (c == '(' || c == ')' || c == '[' || c == ']')
			throw std::runtime_error("Invalid character: brackets not allowed");

		// Process digit
		if (isDigit(c))
		{
			// Check if next non-space character is also a digit (multi-digit number)
			size_t next = i + 1;
			while (next < expression.length() && expression[next] == ' ')
				next++;
			if (next < expression.length() && isDigit(expression[next]) && i + 1 == next)
			{
				// This catches cases like "10" but not "1 0"
				// Actually we need to check if there's no space between digits
			}
			// Check for multi-digit numbers (no space after digit followed by digit)
			if (i + 1 < expression.length() && isDigit(expression[i + 1]))
				throw std::runtime_error("Numbers must be single digits (less than 10)");

			_stack.push(static_cast<double>(c - '0'));
		}
		// Process operator
		else if (isOperator(c))
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Insufficient operands");

			double b = _stack.top();
			_stack.pop();
			double a = _stack.top();
			_stack.pop();

			double result = performOperation(a, b, c);
			_stack.push(result);
		}
		// Invalid character
		else
		{
			throw std::runtime_error("Invalid character");
		}
	}

	// After processing, stack should have exactly one element
	if (_stack.size() != 1)
		throw std::runtime_error("Invalid expression");

	return _stack.top();
}
