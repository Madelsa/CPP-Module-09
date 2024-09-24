/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:19:13 by mahmoud           #+#    #+#             */
/*   Updated: 2024/09/25 00:26:57 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template<typename T>
void print_container(T &con) 
{
	for (typename T::iterator it = con.begin(); it != con.end(); it++) 
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	return;
}

int main( int ac, char **av ) 
{

	if ( ac < 2 ) {
		std::cout << "Invalid input format" << std::endl;
		return -1;
	}

	try {
		clock_t list_start_time = clock();
		std::list<int> numbers_list = PmergeMe<std::list<int>, std::list<std::pair<int, int> > >::parseNumbers(ac, av);
		std::list<int> list_cpy = numbers_list;
		std::list<int> sorted_list = PmergeMe<std::list<int>, std::list<std::pair<int, int> > >::FJMI(numbers_list);
		clock_t list_end_time = clock() - list_start_time;
		double list_sort_time = list_end_time / (double) CLOCKS_PER_SEC * 1e3;

		clock_t vector_start_time = clock();
		std::vector<int> numbers_vector = PmergeMe<std::vector<int>, std::vector<std::pair<int, int> > >::parseNumbers( ac, av );
		std::vector<int> sorted_vector = PmergeMe<std::vector<int>, std::vector<std::pair<int, int> > >::FJMI( numbers_vector );
		clock_t vector_end_time = clock() - vector_start_time;
		double vector_sort_time = vector_end_time / (double) CLOCKS_PER_SEC * 1e3;

		std::cout << "Before: ";
		print_container( list_cpy );
		std::cout << "After: ";
		print_container( sorted_list );

		std::cout << std::fixed << std::setprecision(5);
		std::cout << "Time to process a range of " << list_cpy.size() << " elements with std::list : " << list_sort_time << " ms" << std::endl;

		std::cout << "Time to process a range of " << list_cpy.size() << " elements with std::vector : " << vector_sort_time << " ms" << std::endl;
	} catch( std::runtime_error const &e ) {
		std::cout << e.what() << std::endl;
		return -2;
	}

	return 0;
}

