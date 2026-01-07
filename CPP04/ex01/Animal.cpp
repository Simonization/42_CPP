#include "Animal.hpp"

Animal::Animal(void) : _type("Animal")
{
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(const Animal& src)  : _type(src._type)
{
	std::cout << "Animal copy constructor called" << std::endl;
	*this = src;
}

Animal& Animal::operator=(const Animal& other)
{
	std::cout << "Animal assignment operator called" << std::endl;
	if (this != &other)
		this->_type = other._type;
	return (*this);
}

Animal::~Animal(void)
{
	std::cout << "Animal destructor called" << std::endl;
}

void Animal::makeSound(void) const
{
	std::cout << "What Does the Fox Say?" << std::endl;
}

std::string Animal::getType(void) const
{
	return (this->_type);
}