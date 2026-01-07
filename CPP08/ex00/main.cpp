#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main(void)
{
	std::cout << "=== Testing with std::vector<int> ===" << std::endl;
	{
		std::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(4);
		vec.push_back(5);

		try
		{
			std::vector<int>::iterator it = easyfind(vec, 1);
			std::cout << "Found first element: " << *it << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}

		try
		{
			std::vector<int>::iterator it = easyfind(vec, 3);
			std::cout << "Found middle element: " << *it << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}

		try
		{
			std::vector<int>::iterator it = easyfind(vec, 5);
			std::cout << "Found last element: " << *it << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}

		try
		{
			std::vector<int>::iterator it = easyfind(vec, 42);
			std::cout << "Found: " << *it << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Expected exception: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Testing with std::list<int> ===" << std::endl;
	{
		std::list<int> lst;
		lst.push_back(10);
		lst.push_back(20);
		lst.push_back(30);
		lst.push_back(40);
		lst.push_back(50);

		try
		{
			std::list<int>::iterator it = easyfind(lst, 30);
			std::cout << "Found element in list: " << *it << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}

		try
		{
			std::list<int>::iterator it = easyfind(lst, 100);
			std::cout << "Found: " << *it << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Expected exception: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Testing with std::deque<int> ===" << std::endl;
	{
		std::deque<int> deq;
		deq.push_back(100);
		deq.push_back(200);
		deq.push_back(300);

		try
		{
			std::deque<int>::iterator it = easyfind(deq, 200);
			std::cout << "Found element in deque: " << *it << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}

		try
		{
			std::deque<int>::iterator it = easyfind(deq, 999);
			std::cout << "Found: " << *it << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Expected exception: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Testing with empty container ===" << std::endl;
	{
		std::vector<int> empty;

		try
		{
			std::vector<int>::iterator it = easyfind(empty, 1);
			std::cout << "Found: " << *it << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Expected exception (empty container): " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Testing with duplicates (first occurrence) ===" << std::endl;
	{
		std::vector<int> dup;
		dup.push_back(5);
		dup.push_back(10);
		dup.push_back(5);
		dup.push_back(20);
		dup.push_back(5);

		try
		{
			std::vector<int>::iterator it = easyfind(dup, 5);
			std::cout << "Found first occurrence of 5: " << *it << std::endl;
			std::cout << "Position (distance from begin): "
			          << std::distance(dup.begin(), it) << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== All tests completed ===" << std::endl;

	return 0;
}
