#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN& src)
{
	_stack = src._stack;
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		_stack = other._stack;
	}
	return *this;
}

RPN::~RPN()
{
}

bool RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isDigit(char c) const
{
	return (c >= '0' && c <= '9');
}

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

double RPN::evaluate(const std::string& expression)
{
	while (!_stack.empty())
		_stack.pop();

	if (expression.empty())
		throw std::runtime_error("Empty expression");

	for (size_t i = 0; i < expression.length(); ++i)
	{
		char c = expression[i];

		if (c == ' ' || c == '\t')
			continue;

		if (c == '(' || c == ')' || c == '[' || c == ']')
			throw std::runtime_error("Invalid character: brackets not allowed");

		if (isDigit(c))
		{
			size_t next = i + 1;
			while (next < expression.length() && expression[next] == ' ')
				next++;

			if (i + 1 < expression.length() && isDigit(expression[i + 1]))
				throw std::runtime_error("Numbers must be single digits (less than 10)");

			_stack.push(static_cast<double>(c - '0'));
		}

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

		else
		{
			throw std::runtime_error("Invalid character");
		}
	}

	if (_stack.size() != 1)
		throw std::runtime_error("Invalid expression");

	return _stack.top();
}
