#include "iter.hpp"

#include <iostream>
#include <string>

// Function taking const reference (for reading)
template <typename T>
void print(T const& elem)
{
	std::cout << elem << " ";
}

// Function taking non-const reference (for modifying)
void increment(int& n)
{
	n++;
}

// Function taking non-const reference for strings
void toUpper(std::string& str)
{
	for (std::size_t i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
	}
}

// Simple print for const string
void printString(std::string const& str)
{
	std::cout << "[" << str << "] ";
}

int main(void)
{
	std::cout << "=== Test 1: int array with print (const ref) ===" << std::endl;
	int intArray[] = {1, 2, 3, 4, 5};
	std::size_t intLen = sizeof(intArray) / sizeof(intArray[0]);
	::iter(intArray, intLen, print<int>);
	std::cout << std::endl;

	std::cout << "\n=== Test 2: int array with increment (non-const ref) ===" << std::endl;
	std::cout << "Before: ";
	::iter(intArray, intLen, print<int>);
	std::cout << std::endl;
	::iter(intArray, intLen, increment);
	std::cout << "After:  ";
	::iter(intArray, intLen, print<int>);
	std::cout << std::endl;

	std::cout << "\n=== Test 3: string array ===" << std::endl;
	std::string strArray[] = {"hello", "world", "iter", "test"};
	std::size_t strLen = sizeof(strArray) / sizeof(strArray[0]);
	std::cout << "Before: ";
	::iter(strArray, strLen, printString);
	std::cout << std::endl;
	::iter(strArray, strLen, toUpper);
	std::cout << "After:  ";
	::iter(strArray, strLen, printString);
	std::cout << std::endl;

	std::cout << "\n=== Test 4: const array (only works with const ref functions) ===" << std::endl;
	int const constArray[] = {10, 20, 30};
	std::size_t constLen = sizeof(constArray) / sizeof(constArray[0]);
	::iter(constArray, constLen, print<int>);
	std::cout << std::endl;

	std::cout << "\n=== Test 5: double array ===" << std::endl;
	double dblArray[] = {1.1, 2.2, 3.3, 4.4};
	std::size_t dblLen = sizeof(dblArray) / sizeof(dblArray[0]);
	::iter(dblArray, dblLen, print<double>);
	std::cout << std::endl;

	std::cout << "\n=== Test 6: char array ===" << std::endl;
	char charArray[] = {'a', 'b', 'c', 'd', 'e'};
	std::size_t charLen = sizeof(charArray) / sizeof(charArray[0]);
	::iter(charArray, charLen, print<char>);
	std::cout << std::endl;

	std::cout << "\n=== Test 7: empty array (length 0) ===" << std::endl;
	int emptyArray[] = {0};
	::iter(emptyArray, 0, print<int>);
	std::cout << "(no output expected)" << std::endl;

	return 0;
}
