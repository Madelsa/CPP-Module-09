/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:47:23 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/09/24 23:30:22 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <cctype>

class RPN 
{
	private:
		std::stack<int> stack;

	public:
		RPN();
		RPN(RPN const &copyTemplate);
		RPN &operator=(RPN const &initTemplate);
		~RPN();
		int	readArg(std::string const &expression);
		bool isOperator(char c);
		void calculate(char op);
};

#endif