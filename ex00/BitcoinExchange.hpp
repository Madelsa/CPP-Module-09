/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:09:31 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/09/24 15:16:01 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>
#include <cstdlib>

class BitcoinExchange 
{
	private:
		std::map<std::string, double> map;

	public:	
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &copyTemplate);
		BitcoinExchange &operator=(BitcoinExchange const &initTemplate);
		~BitcoinExchange();
		void	fillMap(std::string const &fileName);
		void	readInFile(std::string const &fileName);
		void	readLine(std::string const &line);
		double	getExRate(std::string const &date) const;
		bool	isValidDate(std::string const &date) const;
		bool	isValidValue(double value) const;
		bool	isLeapYear(int year) const;
};

#endif