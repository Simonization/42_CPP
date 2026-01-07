/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
