#include "Span.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>

static void printHeader(const std::string& title)
{
	std::cout << std::endl;
	std::cout << "========== " << title << " ==========" << std::endl;
}

// Subject test - expected output: 2 and 14
static void testSubject(void)
{
	printHeader("Subject Test");

	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
}

// Test with 10,000+ numbers
static void testLargeSpan(void)
{
	printHeader("Large Span Test (10,000 numbers)");

	Span sp(10000);

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	for (int i = 0; i < 10000; i++)
	{
		sp.addNumber(std::rand());
	}

	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	std::cout << "Longest span: " << sp.longestSpan() << std::endl;
}

// Test exceptions
static void testExceptions(void)
{
	printHeader("Exception Tests");

	// Test SpanFullException
	std::cout << "Testing SpanFullException:" << std::endl;
	try
	{
		Span sp(3);
		sp.addNumber(1);
		sp.addNumber(2);
		sp.addNumber(3);
		sp.addNumber(4); // Should throw
		std::cout << "  ERROR: No exception thrown" << std::endl;
	}
	catch (const Span::SpanFullException& e)
	{
		std::cout << "  Caught: " << e.what() << std::endl;
	}

	// Test NoSpanException with 0 elements
	std::cout << "Testing NoSpanException (0 elements):" << std::endl;
	try
	{
		Span sp(5);
		sp.shortestSpan(); // Should throw
		std::cout << "  ERROR: No exception thrown" << std::endl;
	}
	catch (const Span::NoSpanException& e)
	{
		std::cout << "  Caught: " << e.what() << std::endl;
	}

	// Test NoSpanException with 1 element
	std::cout << "Testing NoSpanException (1 element):" << std::endl;
	try
	{
		Span sp(5);
		sp.addNumber(42);
		sp.longestSpan(); // Should throw
		std::cout << "  ERROR: No exception thrown" << std::endl;
	}
	catch (const Span::NoSpanException& e)
	{
		std::cout << "  Caught: " << e.what() << std::endl;
	}
}

// Test range insertion with iterators
static void testRangeInsertion(void)
{
	printHeader("Range Insertion Test");

	// Using vector iterators
	std::cout << "Using vector iterators:" << std::endl;
	std::vector<int> vec;
	for (int i = 0; i < 5; i++)
		vec.push_back(i * 10);

	Span sp1(10);
	sp1.addNumbers(vec.begin(), vec.end());
	std::cout << "  Added 5 elements from vector (0, 10, 20, 30, 40)" << std::endl;
	std::cout << "  Shortest span: " << sp1.shortestSpan() << std::endl;
	std::cout << "  Longest span: " << sp1.longestSpan() << std::endl;

	// Using list iterators
	std::cout << "Using list iterators:" << std::endl;
	std::list<int> lst;
	lst.push_back(100);
	lst.push_back(200);
	lst.push_back(150);

	Span sp2(5);
	sp2.addNumbers(lst.begin(), lst.end());
	std::cout << "  Added 3 elements from list (100, 200, 150)" << std::endl;
	std::cout << "  Shortest span: " << sp2.shortestSpan() << std::endl;
	std::cout << "  Longest span: " << sp2.longestSpan() << std::endl;

	// Test range insertion that exceeds capacity
	std::cout << "Testing range overflow:" << std::endl;
	try
	{
		Span sp3(3);
		sp3.addNumbers(vec.begin(), vec.end()); // 5 elements, capacity 3
		std::cout << "  ERROR: No exception thrown" << std::endl;
	}
	catch (const Span::SpanFullException& e)
	{
		std::cout << "  Caught: " << e.what() << std::endl;
	}
}

// Test copy constructor and assignment operator
static void testCopyAndAssignment(void)
{
	printHeader("Copy Constructor & Assignment Test");

	Span original(5);
	original.addNumber(1);
	original.addNumber(100);
	original.addNumber(50);

	// Test copy constructor
	std::cout << "Copy constructor:" << std::endl;
	Span copy(original);
	std::cout << "  Original - Shortest: " << original.shortestSpan();
	std::cout << ", Longest: " << original.longestSpan() << std::endl;
	std::cout << "  Copy - Shortest: " << copy.shortestSpan();
	std::cout << ", Longest: " << copy.longestSpan() << std::endl;

	// Modify original to prove deep copy
	original.addNumber(200);
	std::cout << "After modifying original:" << std::endl;
	std::cout << "  Original - Longest: " << original.longestSpan() << std::endl;
	std::cout << "  Copy - Longest: " << copy.longestSpan() << std::endl;

	// Test assignment operator
	std::cout << "Assignment operator:" << std::endl;
	Span assigned(10);
	assigned.addNumber(999);
	assigned = original;
	std::cout << "  Assigned - Shortest: " << assigned.shortestSpan();
	std::cout << ", Longest: " << assigned.longestSpan() << std::endl;
}

// Test edge cases
static void testEdgeCases(void)
{
	printHeader("Edge Cases Test");

	// Negative numbers
	std::cout << "Negative numbers:" << std::endl;
	Span sp1(5);
	sp1.addNumber(-100);
	sp1.addNumber(-50);
	sp1.addNumber(0);
	sp1.addNumber(50);
	sp1.addNumber(100);
	std::cout << "  Numbers: -100, -50, 0, 50, 100" << std::endl;
	std::cout << "  Shortest span: " << sp1.shortestSpan() << std::endl;
	std::cout << "  Longest span: " << sp1.longestSpan() << std::endl;

	// Duplicate numbers
	std::cout << "Duplicate numbers:" << std::endl;
	Span sp2(5);
	sp2.addNumber(42);
	sp2.addNumber(42);
	sp2.addNumber(42);
	sp2.addNumber(100);
	sp2.addNumber(100);
	std::cout << "  Numbers: 42, 42, 42, 100, 100" << std::endl;
	std::cout << "  Shortest span: " << sp2.shortestSpan() << std::endl;
	std::cout << "  Longest span: " << sp2.longestSpan() << std::endl;

	// Two identical numbers (span should be 0)
	std::cout << "Two identical numbers:" << std::endl;
	Span sp3(2);
	sp3.addNumber(7);
	sp3.addNumber(7);
	std::cout << "  Numbers: 7, 7" << std::endl;
	std::cout << "  Shortest span: " << sp3.shortestSpan() << std::endl;
	std::cout << "  Longest span: " << sp3.longestSpan() << std::endl;

	// Exactly two numbers
	std::cout << "Exactly two numbers:" << std::endl;
	Span sp4(2);
	sp4.addNumber(10);
	sp4.addNumber(20);
	std::cout << "  Numbers: 10, 20" << std::endl;
	std::cout << "  Shortest span: " << sp4.shortestSpan() << std::endl;
	std::cout << "  Longest span: " << sp4.longestSpan() << std::endl;
}

int main(void)
{
	testSubject();
	testLargeSpan();
	testExceptions();
	testRangeInsertion();
	testCopyAndAssignment();
	testEdgeCases();

	std::cout << std::endl;
	return 0;
}
