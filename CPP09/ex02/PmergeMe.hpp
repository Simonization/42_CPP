#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <utility>

class PmergeMe
{
private:
	std::vector<int> _vec;
	std::deque<int> _deq;

	// Vector implementation
	void mergeInsertSortVector(std::vector<int>& arr);
	void binaryInsertVector(std::vector<int>& arr, int value, size_t end);

	// Deque implementation
	void mergeInsertSortDeque(std::deque<int>& arr);
	void binaryInsertDeque(std::deque<int>& arr, int value, size_t end);

	// Helper to generate Jacobsthal insertion order
	std::vector<size_t> getJacobsthalOrder(size_t n);

public:
	PmergeMe();
	PmergeMe(const PmergeMe& src);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	void parseInput(int argc, char** argv);
	void sortAndDisplay();
};

#endif
