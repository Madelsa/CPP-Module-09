/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:47:22 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/09/24 16:18:34 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(RPN const &copyTemplate) 
{
	this->operands = copyTemplate.operands;
}

RPN &RPN::operator=(RPN const &initTemplate)
{
	if ( this != &initTemplate ) 
    {
		this->operands = initTemplate.operands;
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

int	RPN::calculate(std::string const &expression) 
{
	std::istringstream	iss(expression);
	std::string			token;

	while (iss >> token) 
    {
		if (token.length() == 1 && isOperator(token[0])) 
        {
			performOperation(token[0]);
		} 
        else 
        {
			if (!isAllDigits(token)) 
            {
				throw std::runtime_error("Invalid entry: " + token);
			}

			int num;
			std::istringstream(token) >> num;	
			if (num < 0 || num > 9)
            {
				throw std::runtime_error( "Invalid number: " + token );
			}
			operands.push(num);
		}
	}

	if (operands.size() != 1) 
    {
		throw std::runtime_error( "Invalid expression");
	}
	return operands.top();
}

bool	RPN::isOperator(char c) 
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

void	RPN::performOperation(char op) 
{
	if ( this->operands.size() < 2 ) 
    {
		throw std::runtime_error( "Not Enough Operands for Operation" );
	}
	int b = this->operands.top();
	this->operands.pop();
	int a = this->operands.top();
	this->operands.pop();

	switch (op) 
    {
		case '+':
			operands.push( a + b );
			break;
		case '-':
			operands.push( a - b );
			break;
		case '*':
			operands.push( a * b );
			break;
		case '/':
			if ( b == 0 ) 
            {
				throw std::runtime_error("Division by Zero");
			}
			operands.push( a / b );
			break;
	}
	return;
}