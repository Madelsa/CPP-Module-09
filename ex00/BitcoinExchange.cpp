/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:09:30 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/09/24 15:21:27 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &copyTemplate) 
{
	this->map = copyTemplate.map;	
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &initTemplate) 
{
	if ( this != &initTemplate ) 
    {
		this->map = initTemplate.map;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::isValidValue(double value) const 
{
	return value >= 0 && value <= 1000;
}

bool BitcoinExchange::isLeapYear(int year) const 
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int	daysBetween(std::string const &date1, std::string const &date2) 
{

	std::tm tm1 = {};
	std::tm tm2 = {};
	std::istringstream iss1(date1);
	std::istringstream iss2(date2);
	
	iss1 >> tm1.tm_year;
	iss1.ignore();
	iss1 >> tm1.tm_mon;
	iss1.ignore();
	iss1 >> tm1.tm_mday;
	
	iss2 >> tm2.tm_year;
	iss2.ignore();
	iss2 >> tm2.tm_mon;
	iss2.ignore();
	iss2 >> tm2.tm_mday;

	tm1.tm_year -= 1900;
	tm1.tm_mon -= 1;
	tm2.tm_year -= 1900;
	tm2.tm_mon -= 1;
	
	std::time_t time1 = std::mktime(&tm1);
	std::time_t time2 = std::mktime(&tm2);
	return std::abs(static_cast<int>(std::difftime(time1, time2) / (60 * 60 * 24)));
}

double	BitcoinExchange::getExRate(std::string const &date) const 
{
	std::map<std::string, double>::const_iterator it = map.lower_bound(date);

	if (it == map.end()) 
	{
		it--;
	} 
	else if (it == map.begin() && it->first > date) 
	{
		throw std::runtime_error("Error: no exchange rate available for the given date.");
	} 
	else if (it->first != date)
	{
		std::map<std::string, double>::const_iterator prev = it;
		prev--;
		if (daysBetween(date, prev->first) <= daysBetween(date, it->first)) 
		{
			it = prev;
		}
	}
	return it->second;
}

void BitcoinExchange::readLine(std::string const &line) 
{
	std::istringstream	iss(line);
	std::string			date;
	double				value;

	if (std::getline(iss, date, '|') && (iss >> value)) 
	{
		date = date.substr(0, date.find_last_not_of(" \t") + 1);
		if (!isValidDate(date)) 
		{
			std::cout << "Error: Bad input => " << date << std::endl;
		} 
		else if (!isValidValue(value)) 
		{
			if (value < 0) 
			{
				std::cout << "Error: non-positive value found." << std::endl;
			} 
			else 
			{
				std::cout << "Error: number is too large." << std::endl;
			}
		} 
		else 
		{
			try 
			{
				double rate = getExRate(date);
				double result = value * rate;
				std::cout << date << " => " << value << " = " << result << std::endl;
			}
			catch (std::exception const &e) 
			{
				std::cout << "Error: " << e.what() << std::endl;
			}
		}
	} else 
	{
		std::cout << "Error: Bad input => " << line << std::endl;
	}
}

void BitcoinExchange::readInFile(std::string const &fileName) 
{
	
	std::ifstream infile(fileName.c_str());
	if (!infile.is_open())
	{
		std::cout << "Error: could not open input file." << std::endl;
		return;
	}
	std::string	line;
	std::getline(infile, line);
	while (std::getline(infile, line)) 
	{
		readLine(line);
	}
}

void BitcoinExchange::fillMap(std::string const &fileName) 
{
	std::string	line;
	std::ifstream infile(fileName.c_str());
	if (!infile.is_open()) 
    {
		std::cout << "Error: could not open input file." << std::endl;
		return;
	}
	std::getline(infile, line);
	while (std::getline(infile, line)) 
    {
		std::istringstream	iss(line);
		std::string			date;
		double				rate;

		if (std::getline(iss, date, ',') && (iss >> rate)) 
        {
			map[date] = rate;
		}
	}
	return;
}

bool BitcoinExchange::isValidDate(std::string const &date) const 
{

	if (date.length() != 10 || date[4] != '-' || date[7] != '-') 
	{
		return false;
	}
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	if (year < 1 || month < 1 || month > 12 || day < 1) 
	{
		return false;
	}
	
	const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2) 
	{
		if (isLeapYear(year)) 
		{
			if (day > 29) 
			{
				return false;
			}
		}
		else 
		{
			if (day > 28) 
			{
				return false;
			}
		}
	} 
	else
	{
		if (day > daysInMonth[month])
		{
			return false;
		}
	}
	return true;
}

