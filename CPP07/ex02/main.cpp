#include "Array.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#define MAX_VAL 750

int main(void)
{
	std::cout << "=== Test 1: Empty array construction ===" << std::endl;
	{
		Array<int> empty;
		std::cout << "Empty array size: " << empty.size() << std::endl;
		try
		{
			empty[0] = 42;
			std::cout << "ERROR: Should have thrown exception" << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Caught exception: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test 2: Array with size construction ===" << std::endl;
	{
		Array<int> numbers(5);
		std::cout << "Array size: " << numbers.size() << std::endl;
		std::cout << "Default initialized values: ";
		for (unsigned int i = 0; i < numbers.size(); i++)
			std::cout << numbers[i] << " ";
		std::cout << std::endl;

		for (unsigned int i = 0; i < numbers.size(); i++)
			numbers[i] = i * 10;
		std::cout << "Modified values: ";
		for (unsigned int i = 0; i < numbers.size(); i++)
			std::cout << numbers[i] << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test 3: Copy constructor (deep copy) ===" << std::endl;
	{
		Array<int> original(3);
		original[0] = 1;
		original[1] = 2;
		original[2] = 3;

		Array<int> copy(original);

		std::cout << "Original: ";
		for (unsigned int i = 0; i < original.size(); i++)
			std::cout << original[i] << " ";
		std::cout << std::endl;

		std::cout << "Copy: ";
		for (unsigned int i = 0; i < copy.size(); i++)
			std::cout << copy[i] << " ";
		std::cout << std::endl;

		copy[0] = 100;
		std::cout << "After modifying copy[0] to 100:" << std::endl;
		std::cout << "Original[0]: " << original[0] << " (should be 1)" << std::endl;
		std::cout << "Copy[0]: " << copy[0] << " (should be 100)" << std::endl;
	}

	std::cout << std::endl << "=== Test 4: Assignment operator (deep copy) ===" << std::endl;
	{
		Array<int> arr1(3);
		arr1[0] = 10;
		arr1[1] = 20;
		arr1[2] = 30;

		Array<int> arr2;
		arr2 = arr1;

		std::cout << "arr1: ";
		for (unsigned int i = 0; i < arr1.size(); i++)
			std::cout << arr1[i] << " ";
		std::cout << std::endl;

		std::cout << "arr2 after assignment: ";
		for (unsigned int i = 0; i < arr2.size(); i++)
			std::cout << arr2[i] << " ";
		std::cout << std::endl;

		arr1[0] = 999;
		std::cout << "After modifying arr1[0] to 999:" << std::endl;
		std::cout << "arr1[0]: " << arr1[0] << " (should be 999)" << std::endl;
		std::cout << "arr2[0]: " << arr2[0] << " (should be 10)" << std::endl;
	}

	std::cout << std::endl << "=== Test 5: Out of bounds exception ===" << std::endl;
	{
		Array<int> arr(5);
		try
		{
			std::cout << "Trying to access index 5 (out of bounds)..." << std::endl;
			arr[5] = 42;
			std::cout << "ERROR: Should have thrown exception" << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Caught exception: " << e.what() << std::endl;
		}

		try
		{
			std::cout << "Trying to access index 1000 (out of bounds)..." << std::endl;
			int x = arr[1000];
			(void)x;
			std::cout << "ERROR: Should have thrown exception" << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Caught exception: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test 6: Array of strings ===" << std::endl;
	{
		Array<std::string> strings(3);
		strings[0] = "Hello";
		strings[1] = "World";
		strings[2] = "!";

		for (unsigned int i = 0; i < strings.size(); i++)
			std::cout << strings[i] << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test 7: Const array access ===" << std::endl;
	{
		Array<int> arr(3);
		arr[0] = 42;
		arr[1] = 21;
		arr[2] = 84;

		const Array<int> constArr(arr);
		std::cout << "Const array values: ";
		for (unsigned int i = 0; i < constArr.size(); i++)
			std::cout << constArr[i] << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test 8: Large array (subject test) ===" << std::endl;
	{
		Array<int> numbers(MAX_VAL);
		int* mirror = new int[MAX_VAL];

		srand(time(NULL));
		for (int i = 0; i < MAX_VAL; i++)
		{
			const int value = rand();
			numbers[i] = value;
			mirror[i] = value;
		}

		{
			Array<int> tmp = numbers;
			Array<int> test(tmp);
		}

		for (int i = 0; i < MAX_VAL; i++)
		{
			if (mirror[i] != numbers[i])
			{
				std::cerr << "didn't save the same value!!" << std::endl;
				delete[] mirror;
				return 1;
			}
		}

		try
		{
			numbers[-2] = 0;
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught expected exception for negative index" << std::endl;
		}

		try
		{
			numbers[MAX_VAL] = 0;
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught expected exception for MAX_VAL index" << std::endl;
		}

		delete[] mirror;
		std::cout << "Large array test passed!" << std::endl;
	}

	std::cout << std::endl << "=== Test 9: Self-assignment ===" << std::endl;
	{
		Array<int> arr(3);
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;

		arr = arr;

		std::cout << "After self-assignment: ";
		for (unsigned int i = 0; i < arr.size(); i++)
			std::cout << arr[i] << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "All tests completed!" << std::endl;
	return 0;
}
