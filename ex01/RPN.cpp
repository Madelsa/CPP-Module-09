/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:47:22 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/09/24 23:30:32 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(RPN const &copyTemplate)
{
	this->stack = copyTemplate.stack;
}

RPN &RPN::operator=(RPN const &initTemplate)
{
	if (this != &initTemplate)
	{
		this->stack = initTemplate.stack;
	}
	return *this;
}

RPN::~RPN() {}

bool isAllDigits(const std::string &str)
{
	for (std::string::const_iterator it = str.begin(); it != str.end(); it++)
	{
		if (!std::isdigit(*it))
		{
			return false;
		}
	}
	return true;
}

bool RPN::isOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

void RPN::calculate(char c)
{
	if (this->stack.size() < 2)
	{
		throw std::runtime_error("Not Enough Operands for Operation");
	}
	int b = this->stack.top();
	this->stack.pop();
	int a = this->stack.top();
	this->stack.pop();

	if (c == '+')
	{
		stack.push(a + b);
	}
	else if (c == '-')
	{
		stack.push(a - b);
	}
	else if (c == '*')
	{
		stack.push(a * b);
	}
	else if (c == '/')
	{
		if (b == 0)
		{
			throw std::runtime_error("Denominator 0 found.");
		}
		stack.push(a / b);
	}
	return;
}

int RPN::readArg(std::string const &arg)
{
	std::istringstream iss(arg);
	std::string element;

	while (iss >> element)
	{
		if (element.length() == 1 && isOperator(element[0]))
		{
			calculate(element[0]);
		}
		else
		{
			if (!isAllDigits(element))
			{
				throw std::invalid_argument("Non-digit element found: " + element);
			}
			int n;
			std::istringstream(element) >> n;
			if (n < 0 || n > 9)
			{
				throw std::out_of_range("Invalid number: " + element);
			}
			stack.push(n);
		}
	}
	if (stack.size() != 1)
	{
		throw std::logic_error("Expression received is invalid");
	}
	return stack.top();
}
