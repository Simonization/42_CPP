#include "AAnimal.hpp"

AAnimal::AAnimal(void) : _type("AAnimal")
{
    std::cout << "AAnimal default constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal& src) : _type(src._type)
{
    std::cout << "AAnimal copy constructor called" << std::endl;
}

AAnimal& AAnimal::operator=(const AAnimal& other)
{
    std::cout << "AAnimal copy assignment operator called" << std::endl;
    if (this != &other)
        this->_type = other._type;
    return *this;
}

AAnimal::~AAnimal(void)
{
    std::cout << "AAnimal destructor called" << std::endl;
}

void AAnimal::makeSound(void) const
{
	std::cout << "What Does the Fox Say?" << std::endl;
}

std::string AAnimal::get_type(void) const
{
    return this->_type;
}