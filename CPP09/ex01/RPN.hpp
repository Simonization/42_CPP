#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <stdexcept>

class RPN
{
private:
	std::stack<double> _stack;

	bool isOperator(char c) const;
	bool isDigit(char c) const;
	double performOperation(double a, double b, char op) const;

public:
	RPN();
	RPN(const RPN& src);
	RPN& operator=(const RPN& other);
	~RPN();

	double evaluate(const std::string& expression);
};

#endif
