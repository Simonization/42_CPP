#include "Bureaucrat.hpp"

#include <iostream>

int main(void)
{
	std::cout << "\n===== TEST 1: Valid Bureaucrat Creation =====" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 75);
		std::cout << bob << std::endl;

		Bureaucrat alice("Alice", 1);
		std::cout << alice << std::endl;

		Bureaucrat charlie("Charlie", 150);
		std::cout << charlie << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 2: Invalid Grade (Too High) =====" << std::endl;
	try
	{
		Bureaucrat invalid("Invalid", 0);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 3: Invalid Grade (Too Low) =====" << std::endl;
	try
	{
		Bureaucrat invalid("Invalid", 151);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 4: Increment Grade =====" << std::endl;
	try
	{
		Bureaucrat john("John", 5);
		std::cout << "Before increment: " << john << std::endl;

		john.incrementGrade();
		std::cout << "After 1st increment: " << john << std::endl;

		john.incrementGrade();
		std::cout << "After 2nd increment: " << john << std::endl;

		john.incrementGrade();
		std::cout << "After 3rd increment: " << john << std::endl;

		john.incrementGrade();
		std::cout << "After 4th increment: " << john << std::endl;

		// This should throw an exception
		john.incrementGrade();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 5: Decrement Grade =====" << std::endl;
	try
	{
		Bureaucrat jane("Jane", 148);
		std::cout << "Before decrement: " << jane << std::endl;

		jane.decrementGrade();
		std::cout << "After 1st decrement: " << jane << std::endl;

		jane.decrementGrade();
		std::cout << "After 2nd decrement: " << jane << std::endl;

		// This should throw an exception
		jane.decrementGrade();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 6: Copy Constructor and Assignment =====" << std::endl;
	try
	{
		Bureaucrat original("Original", 42);
		std::cout << "Original: " << original << std::endl;

		Bureaucrat copy(original);
		std::cout << "Copy: " << copy << std::endl;

		Bureaucrat assigned("Temp", 100);
		std::cout << "Before assignment: " << assigned << std::endl;

		assigned = original;
		std::cout << "After assignment: " << assigned << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 7: Edge Cases =====" << std::endl;
	try
	{
		Bureaucrat edge1("Edge1", 1);
		std::cout << edge1 << " - Attempting to increment..." << std::endl;
		edge1.incrementGrade();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	try
	{
		Bureaucrat edge2("Edge2", 150);
		std::cout << edge2 << " - Attempting to decrement..." << std::endl;
		edge2.decrementGrade();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	return 0;
}
