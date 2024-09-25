/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:19:12 by mahmoud           #+#    #+#             */
/*   Updated: 2024/09/25 09:22:45 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <algorithm>
# include <deque>
# include <iomanip>
# include <iostream>
# include <iterator>
# include <list>
# include <sstream>
# include <string>
# include <utility>
# include <vector>

typedef std::pair<int, bool> oddEntry;
template <typename N, typename P>
class PmergeMe
{
  private:
	PmergeMe();
	PmergeMe(PmergeMe const &copyTemplate);
	PmergeMe &operator=(PmergeMe const &initTemplate);
	~PmergeMe();
	static oddEntry checkOddEntry(N &numbers);
	static P recursionMS(P &pairs);
	static void pushLargestNums(P &pairsSorted, N &numsSorted);
	static void insertSortSmallest(P &pairsSorted, N &sorted_num);

  public:
	static N readNums(int ac, char **av);
	static N fordJ(N &numbers);
};

template <typename N, typename P>
N PmergeMe<N, P>::readNums(int ac, char **av)
{
	N	numbers;
	int	n;

	n = -1;
	for (int i = 1; i < ac; i++)
	{
		std::istringstream iss((std::string(av[i])));
		iss >> n;
		if (iss.fail() || !iss.eof() || n < 0)
		{
			throw std::runtime_error("Error: Invalid Input.");
		}
		else
		{
			numbers.push_back(n);
		}
	}
	return (numbers);
}

template <typename N, typename P>
N PmergeMe<N, P>::fordJ(N &numbers)
{
	oddEntry	remainingNum;
	int			first;
	int			second;

	remainingNum = checkOddEntry(numbers);
	P pairs(0);
	P pairsSorted(0);
	N numsSorted(0);
	while (!numbers.empty() && numbers.size() > 1)
	{
		first = numbers.front();
		numbers.erase(numbers.begin());
		second = numbers.front();
		numbers.erase(numbers.begin());
		if (first > second)
		{
			std::swap(first, second);
		}
		pairs.push_back(std::make_pair(first, second));
	}
	if (!pairs.empty())
	{
		pairsSorted = recursionMS(pairs);
		pushLargestNums(pairsSorted, numsSorted);
		insertSortSmallest(pairsSorted, numsSorted);
	}
	if (remainingNum.second)
	{
		typename N::iterator insertPos = std::lower_bound(numsSorted.begin(),
															numsSorted.end(),
															remainingNum.first);
		numsSorted.insert(insertPos, remainingNum.first);
	}
	return (numsSorted);
}

template <typename N, typename P>
oddEntry PmergeMe<N, P>::checkOddEntry(N &numbers)
{
	oddEntry	remainingNum;

	remainingNum = std::make_pair(0, false);
	if (((numbers.size()) % 2 != 0))
	{
		remainingNum.first = numbers.back();
		remainingNum.second = true;
		numbers.pop_back();
	}
	return (remainingNum);
}

bool	compareOperation(std::pair<int, int> const &left, std::pair<int,
		int> const &right)
{
	return (left.second < right.second);
}

template <typename N, typename P>
P PmergeMe<N, P>::recursionMS(P &pairs)
{
	size_t	mid;

	P pairsSorted(0);
	if (pairs.size() == 1)
	{
		return (pairs);
	}
	typename P::iterator it = pairs.begin();
	mid = pairs.size() / 2;
	std::advance(it, mid);
	P leftPart(pairs.begin(), it);
	P rightPart(it, pairs.end());
	leftPart = recursionMS(leftPart);
	rightPart = recursionMS(rightPart);
	std::merge(leftPart.begin(), leftPart.end(), rightPart.begin(),
			rightPart.end(), std::back_inserter(pairsSorted), compareOperation);
	return (pairsSorted);
}

template <typename N, typename P>
void PmergeMe<N, P>::pushLargestNums(P &pairsSorted, N &numsSorted)
{
	for (typename P::iterator it = pairsSorted.begin(); it != pairsSorted.end(); it++)
	{
		numsSorted.push_back(it->second);
	}
	return ;
}

template <typename N, typename P>
void PmergeMe<N, P>::insertSortSmallest(P &pairsSorted, N &numsSorted)
{
	for (typename P::iterator it = pairsSorted.begin(); it != pairsSorted.end(); it++)
	{
		typename N::iterator insertPos = std::lower_bound(numsSorted.begin(),
				numsSorted.end(), it->first);
		numsSorted.insert(insertPos, it->first);
	}
	return ;
}

template <typename T>
void	print(T &con)
{
	for (typename T::iterator it = con.begin(); it != con.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	return ;
}

#endif