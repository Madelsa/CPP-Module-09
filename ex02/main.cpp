/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:19:13 by mahmoud           #+#    #+#             */
/*   Updated: 2024/09/25 09:21:22 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	clock_t	listStartTime;
	clock_t	listEndTime;
	double	listTimeToSort;
	clock_t	vectorStartTime;
	clock_t	vectorEndTime;
	double	vectorTimeToSort;

	if (ac < 2)
	{
		std::cout << "Invalid input format" << std::endl;
		return -1;
	}
	try
	{
		listStartTime = clock();
		std::list<int> numsList = PmergeMe<std::list<int>,
			std::list<std::pair<int, int> > >::readNums(ac, av);
		std::list<int> beforeSorting = numsList;
		std::list<int> afterSorting = PmergeMe<std::list<int>,
			std::list<std::pair<int, int> > >::fordJ(numsList);
		listEndTime = clock() - listStartTime;
		listTimeToSort = listEndTime / (double)CLOCKS_PER_SEC * 1000;
		vectorStartTime = clock();
		std::vector<int> numbers_vector = PmergeMe<std::vector<int>,
		std::vector<std::pair<int, int> > >::readNums(ac, av);
		std::vector<int> sorted_vector = PmergeMe<std::vector<int>,
		std::vector<std::pair<int, int> > >::fordJ(numbers_vector);
		vectorEndTime = clock() - vectorStartTime;
		vectorTimeToSort = vectorEndTime / (double)CLOCKS_PER_SEC * 1000;
		
		std::cout << "Before: ";
		print(beforeSorting);
		std::cout << "After: ";
		print(afterSorting);
		std::cout << std::fixed << std::setprecision(5);
		std::cout << "Time to sort " << beforeSorting.size() << " elements with std::list : " << listTimeToSort << " ms" << std::endl;
		std::cout << "Time to sort " << beforeSorting.size() << " elements with std::vector : " << vectorTimeToSort << " ms" << std::endl;
	}
	catch (std::runtime_error const &e)
	{
		std::cout << e.what() << std::endl;
	}
}
