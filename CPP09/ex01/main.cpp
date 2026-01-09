#include "RPN.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	try
	{
		RPN calculator;
		double result = calculator.evaluate(argv[1]);

		if (result == static_cast<int>(result))
			std::cout << static_cast<int>(result) << std::endl;
		else
			std::cout << result << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	return 0;
}
