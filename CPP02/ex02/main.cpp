#include <iostream>
#include "Fixed.hpp"

int main(void)
{
	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;

	std::cout << b << std::endl;

	std::cout << Fixed::max(a, b) << std::endl;

	std::cout << "\n--- Simon Testing Operators ---" << std::endl;
	
	// Test comparison operators
	Fixed c(10);
	Fixed d(20);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "c > d: " << (c > d) << std::endl;
	std::cout << "c < d: " << (c < d) << std::endl;
	std::cout << "c >= d: " << (c >= d) << std::endl;
	std::cout << "c <= d: " << (c <= d) << std::endl;
	std::cout << "c == d: " << (c == d) << std::endl;
	std::cout << "c != d: " << (c != d) << std::endl;

	// Test arithmetic operators
	Fixed e(5.5f);
	Fixed f(2.5f);
	std::cout << "\ne = " << e << ", f = " << f << std::endl;
	std::cout << "e + f = " << (e + f) << std::endl;
	std::cout << "e - f = " << (e - f) << std::endl;
	std::cout << "e * f = " << (e * f) << std::endl;
	std::cout << "e / f = " << (e / f) << std::endl;

	// Test min/max functions
	std::cout << "\nmin(c, d) = " << Fixed::min(c, d) << std::endl;
	std::cout << "max(c, d) = " << Fixed::max(c, d) << std::endl;

	// Test decrement operators
	Fixed g(1);
	std::cout << "\ng = " << g << std::endl;
	std::cout << "--g = " << --g << std::endl;
	std::cout << "g = " << g << std::endl;
	std::cout << "g-- = " << g-- << std::endl;
	std::cout << "g = " << g << std::endl;

	return 0;
}