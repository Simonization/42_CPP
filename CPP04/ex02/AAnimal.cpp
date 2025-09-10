#include "AAnimal.hpp"

// Default constructor
AAnimal::AAnimal(void) : type("AAnimal")
{
    std::cout << "AAnimal default constructor called" << std::endl;
}

// Copy constructor
AAnimal::AAnimal(const AAnimal& src) : type(src.type)
{
    std::cout << "AAnimal copy constructor called" << std::endl;
}

// Copy assignment operator
AAnimal& AAnimal::operator=(const AAnimal& rhs)
{
    std::cout << "AAnimal copy assignment operator called" << std::endl;
    if (this != &rhs)
    {
        this->type = rhs.type;
    }
    return *this;
}

// Destructor
AAnimal::~AAnimal(void)
{
    std::cout << "AAnimal destructor called" << std::endl;
}

// Getter for type
std::string AAnimal::getType(void) const
{
    return this->type;
}