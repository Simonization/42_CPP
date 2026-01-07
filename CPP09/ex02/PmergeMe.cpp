#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <algorithm>
#include <iomanip>

// Orthodox Canonical Form
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& src) : _vec(src._vec), _deq(src._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

// Input parsing and validation
void PmergeMe::parseInput(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];

		if (arg.empty())
			throw std::invalid_argument("Empty argument");

		// Check for negative sign
		if (arg[0] == '-')
			throw std::invalid_argument("Negative number");

		// Check all characters are digits
		for (size_t j = 0; j < arg.length(); ++j)
		{
			if (!std::isdigit(arg[j]))
				throw std::invalid_argument("Invalid character");
		}

		// Parse to long and check overflow
		char* endptr;
		long num = std::strtol(arg.c_str(), &endptr, 10);

		if (*endptr != '\0' || num > INT_MAX || num < 0)
			throw std::invalid_argument("Invalid number");

		_vec.push_back(static_cast<int>(num));
		_deq.push_back(static_cast<int>(num));
	}

	if (_vec.empty())
		throw std::invalid_argument("No numbers provided");
}

// Generate Jacobsthal-based insertion order for n elements
std::vector<size_t> PmergeMe::getJacobsthalOrder(size_t n)
{
	std::vector<size_t> order;
	if (n == 0)
		return order;

	// Generate Jacobsthal numbers
	std::vector<size_t> jacob;
	jacob.push_back(0);
	jacob.push_back(1);
	while (jacob.back() < n)
	{
		size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
		jacob.push_back(next);
	}

	// Build insertion order based on Jacobsthal sequence
	// Insert at positions: J(k), J(k)-1, ..., J(k-1)+1 for each k
	std::vector<bool> used(n, false);

	for (size_t k = 1; k < jacob.size(); ++k)
	{
		size_t start = jacob[k];
		size_t end = jacob[k - 1];

		// Clamp start to valid range
		if (start > n)
			start = n;

		// Insert from start down to end+1
		for (size_t i = start; i > end; --i)
		{
			if (i - 1 < n && !used[i - 1])
			{
				order.push_back(i - 1);
				used[i - 1] = true;
			}
		}
	}

	// Add any remaining indices (shouldn't happen with correct Jacobsthal, but safety)
	for (size_t i = 0; i < n; ++i)
	{
		if (!used[i])
			order.push_back(i);
	}

	return order;
}

// Binary insertion for vector
void PmergeMe::binaryInsertVector(std::vector<int>& arr, int value, size_t end)
{
	size_t left = 0;
	size_t right = end;

	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (arr[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	arr.insert(arr.begin() + static_cast<long>(left), value);
}

// Ford-Johnson merge-insert sort for vector
void PmergeMe::mergeInsertSortVector(std::vector<int>& arr)
{
	size_t n = arr.size();
	if (n <= 1)
		return;

	// Step 1: Create pairs and compare (larger first, smaller second)
	std::vector<std::pair<int, int> > pairs;
	bool hasStraggler = (n % 2 != 0);
	int straggler = hasStraggler ? arr[n - 1] : 0;

	for (size_t i = 0; i + 1 < n; i += 2)
	{
		if (arr[i] > arr[i + 1])
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
		else
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
	}

	// Step 2: Recursively sort by the larger elements
	// We need to sort pairs by their 'first' (larger) element
	if (pairs.size() > 1)
	{
		// Extract larger elements for recursive sorting
		std::vector<int> larger;
		for (size_t i = 0; i < pairs.size(); ++i)
			larger.push_back(pairs[i].first);

		// Recursively sort the larger elements
		mergeInsertSortVector(larger);

		// Rebuild pairs in sorted order based on larger elements
		std::vector<std::pair<int, int> > sortedPairs;
		std::vector<bool> usedPairs(pairs.size(), false);

		for (size_t i = 0; i < larger.size(); ++i)
		{
			for (size_t j = 0; j < pairs.size(); ++j)
			{
				if (!usedPairs[j] && pairs[j].first == larger[i])
				{
					sortedPairs.push_back(pairs[j]);
					usedPairs[j] = true;
					break;
				}
			}
		}
		pairs = sortedPairs;
	}

	// Step 3: Build main chain with sorted larger elements
	// and pending list with smaller elements
	std::vector<int> mainChain;
	std::vector<int> pend;

	for (size_t i = 0; i < pairs.size(); ++i)
	{
		mainChain.push_back(pairs[i].first);
		pend.push_back(pairs[i].second);
	}

	// Step 4: Insert b1 (first pend element) at the beginning
	// It's guaranteed to be smaller than a1 (first mainChain element)
	if (!pend.empty())
	{
		mainChain.insert(mainChain.begin(), pend[0]);
	}

	// Step 5: Insert remaining pend elements using Jacobsthal order
	if (pend.size() > 1)
	{
		std::vector<size_t> insertOrder = getJacobsthalOrder(pend.size() - 1);

		for (size_t i = 0; i < insertOrder.size(); ++i)
		{
			size_t pendIdx = insertOrder[i] + 1; // +1 because we already inserted pend[0]
			if (pendIdx < pend.size())
			{
				// Binary search bound: the corresponding 'a' element position + already inserted count
				binaryInsertVector(mainChain, pend[pendIdx], mainChain.size());
			}
		}
	}

	// Step 6: Insert straggler if exists
	if (hasStraggler)
		binaryInsertVector(mainChain, straggler, mainChain.size());

	arr = mainChain;
}

// Binary insertion for deque
void PmergeMe::binaryInsertDeque(std::deque<int>& arr, int value, size_t end)
{
	size_t left = 0;
	size_t right = end;

	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (arr[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	arr.insert(arr.begin() + static_cast<long>(left), value);
}

// Ford-Johnson merge-insert sort for deque
void PmergeMe::mergeInsertSortDeque(std::deque<int>& arr)
{
	size_t n = arr.size();
	if (n <= 1)
		return;

	// Step 1: Create pairs and compare (larger first, smaller second)
	std::deque<std::pair<int, int> > pairs;
	bool hasStraggler = (n % 2 != 0);
	int straggler = hasStraggler ? arr[n - 1] : 0;

	for (size_t i = 0; i + 1 < n; i += 2)
	{
		if (arr[i] > arr[i + 1])
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
		else
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
	}

	// Step 2: Recursively sort by the larger elements
	if (pairs.size() > 1)
	{
		std::deque<int> larger;
		for (size_t i = 0; i < pairs.size(); ++i)
			larger.push_back(pairs[i].first);

		mergeInsertSortDeque(larger);

		// Rebuild pairs in sorted order
		std::deque<std::pair<int, int> > sortedPairs;
		std::deque<bool> usedPairs(pairs.size(), false);

		for (size_t i = 0; i < larger.size(); ++i)
		{
			for (size_t j = 0; j < pairs.size(); ++j)
			{
				if (!usedPairs[j] && pairs[j].first == larger[i])
				{
					sortedPairs.push_back(pairs[j]);
					usedPairs[j] = true;
					break;
				}
			}
		}
		pairs = sortedPairs;
	}

	// Step 3: Build main chain and pend
	std::deque<int> mainChain;
	std::deque<int> pend;

	for (size_t i = 0; i < pairs.size(); ++i)
	{
		mainChain.push_back(pairs[i].first);
		pend.push_back(pairs[i].second);
	}

	// Step 4: Insert b1 at the beginning
	if (!pend.empty())
	{
		mainChain.push_front(pend[0]);
	}

	// Step 5: Insert remaining using Jacobsthal order
	if (pend.size() > 1)
	{
		std::vector<size_t> insertOrder = getJacobsthalOrder(pend.size() - 1);

		for (size_t i = 0; i < insertOrder.size(); ++i)
		{
			size_t pendIdx = insertOrder[i] + 1;
			if (pendIdx < pend.size())
			{
				binaryInsertDeque(mainChain, pend[pendIdx], mainChain.size());
			}
		}
	}

	// Step 6: Insert straggler
	if (hasStraggler)
		binaryInsertDeque(mainChain, straggler, mainChain.size());

	arr = mainChain;
}

// Main sorting function with timing and display
void PmergeMe::sortAndDisplay()
{
	// Display before
	std::cout << "Before:";
	for (size_t i = 0; i < _vec.size(); ++i)
		std::cout << " " << _vec[i];
	std::cout << std::endl;

	// Sort with vector and measure time
	std::vector<int> vecCopy = _vec;
	clock_t startVec = clock();
	mergeInsertSortVector(vecCopy);
	clock_t endVec = clock();
	double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000.0;

	// Sort with deque and measure time
	std::deque<int> deqCopy = _deq;
	clock_t startDeq = clock();
	mergeInsertSortDeque(deqCopy);
	clock_t endDeq = clock();
	double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000.0;

	// Display after
	std::cout << "After:";
	for (size_t i = 0; i < vecCopy.size(); ++i)
		std::cout << " " << vecCopy[i];
	std::cout << std::endl;

	// Display timing
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << _vec.size()
	          << " elements with std::vector : " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size()
	          << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}
