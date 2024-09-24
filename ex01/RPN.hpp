/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:47:23 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/09/24 16:18:41 by mabdelsa         ###   ########.fr       */
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
		std::stack<int> operands;
		bool isOperator(char c);
		void performOperation(char op);

	public:
		RPN();
		RPN(RPN const &copyTemplate);
		RPN &operator=(RPN const &initTemplate);
		~RPN();
		int	calculate(std::string const &expression);
};

#endif