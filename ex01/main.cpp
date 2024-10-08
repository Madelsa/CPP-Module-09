/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:47:20 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/09/24 23:09:18 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char *av[]) 
{
	if (ac != 2) 
    {
        std::cout << "Invalid input format." << std::endl;
		return -1;
	}
    
	RPN	calculator;
	try 
    {
		std::cout << calculator.readArg(av[1]) << std::endl;
	} 
    catch (const std::exception &e) 
    {
		std::cout << "Error: " << e.what() << std::endl;
	}
}