/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:09:11 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/09/24 14:01:31 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int ac, char **av) 
{
	if (ac != 2) 
    {	
		std::cout << "Invalid input format." << std::endl;
		return -1;
	}
	try 
    {
		BitcoinExchange ex;
		ex.fillMap("data.csv");
		ex.readInFile(av[1]);
	} catch (const std::exception& e) 
    {
		std::cout << e.what() << std::endl;
	}
}