/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:19:12 by mahmoud           #+#    #+#             */
/*   Updated: 2024/09/25 01:18:26 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <vector>
# include <list>
# include <deque>
# include <iterator>
# include <sstream>
# include <utility>
# include <iomanip>
# include <algorithm>

typedef std::pair<int, bool> oddEntry;
template<typename N, typename P>
class PmergeMe 
{

	private:
		PmergeMe();
		PmergeMe(PmergeMe const &copyTemplate);
		PmergeMe &operator=(PmergeMe const &initTemplate);
		~PmergeMe();
		static oddEntry	findStraggler(N &numbers);
		static P			mergeSortSeconds(P &pairs);
		static void			extractLargest(P &sortedPairs, N &sortedNumbers);
		static void			insertSmallest(P &sortedPairs, N &sorted_num);
		
	public:
		static N			parseNumbers(int ac, char **av);
		static N			FJMI(N &numbers);
};

template<typename N, typename P>
N	PmergeMe<N, P>::parseNumbers(int ac, char **av) 
{

	N	numbers;
	int	n = -1;

	for (int i = 1; i < ac; i++) 
	{
		std::istringstream	iss((std::string(av[i])));
		
		iss >> n;
		if (iss.fail() || !iss.eof() || n < 0) 
		{
			throw std::invalid_argument("Error: Invalid Input.");
		} 
		else 
		{
			numbers.push_back(n);
		}
	}
	return numbers;
}

template<typename N, typename P>
N PmergeMe<N, P>::FJMI(N &numbers) 
{
	oddEntry remainingNum = findStraggler(numbers);

	P	pairs(0);
	P	sortedPairs(0);
	N	sortedNumbers(0);

	while (!numbers.empty() && numbers.size() > 1) 
	{
		int first = numbers.front();
		numbers.erase(numbers.begin());
		int second = numbers.front();
		numbers.erase( numbers.begin() );
		if (first > second) 
		{
			std::swap(first, second);
		}
		pairs.push_back(std::make_pair(first, second));
	}
	if (!pairs.empty()) 
	{
		sortedPairs = mergeSortSeconds(pairs);
		extractLargest( sortedPairs, sortedNumbers );
		insertSmallest( sortedPairs, sortedNumbers );
	}
	if (remainingNum.second) 
	{
		typename N::iterator insertPos = std::lower_bound( sortedNumbers.begin(), sortedNumbers.end(), remainingNum.first );
		sortedNumbers.insert( insertPos, remainingNum.first );
	}
	return sortedNumbers;
}

template<typename N, typename P>
oddEntry	PmergeMe<N, P>::findStraggler(N &numbers) 
{
	oddEntry	remainingNum = std::make_pair(0, false);

	if (((numbers.size()) % 2 != 0)) 
	{
		remainingNum.first = numbers.back();
		remainingNum.second = true;
		numbers.pop_back();
	}
	return remainingNum;
}

bool	compSec( std::pair<int, int> const &l, std::pair<int, int> const &r ) {

	return l.second < r.second;
}

template<typename N, typename P>
P			PmergeMe<N, P>::mergeSortSeconds( P &pairs ) {

	P	sortedPairs(0);

	if (pairs.size() == 1) 
	{
		return pairs;
	}
	typename	P::iterator mid_it = pairs.begin();
	size_t	mid = pairs.size() / 2;
	std::advance( mid_it, mid );

	P	left( pairs.begin(), mid_it );
	P	right( mid_it, pairs.end() );

	left = mergeSortSeconds(left);
	right = mergeSortSeconds(right);

	std::merge(left.begin(), left.end(), right.begin(), right.end(),
		std::back_inserter(sortedPairs), compSec);
	return sortedPairs;
}	

template<typename N, typename P>
void			PmergeMe<N, P>::extractLargest( P &sortedPairs, N &sortedNumbers ) {


	for ( typename P::iterator it = sortedPairs.begin(); it != sortedPairs.end(); it++ ) {
		
		sortedNumbers.push_back( it->second );
	}

	return;
}

template<typename N, typename P>
void		PmergeMe<N, P>::insertSmallest( P &sortedPairs, N &sortedNumbers ) {

	for (typename P::iterator it = sortedPairs.begin(); it != sortedPairs.end(); it++) {

		typename	N::iterator insertPos = std::lower_bound( sortedNumbers.begin(), sortedNumbers.end(), it->first );
		sortedNumbers.insert(insertPos, it->first);
	}
	return;
}

#endif