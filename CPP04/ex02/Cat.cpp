#include "Cat.hpp"

// Default constructor
Cat::Cat(void) : AAnimal()
{
    std::cout << "Cat default constructor called" << std::endl;
    this->type = "Cat";
    this->brain = new Brain();
}

// Copy constructor
Cat::Cat(const Cat& src) : AAnimal(src)
{
    std::cout << "Cat copy constructor called" << std::endl;
    this->brain = new Brain(*src.brain);
}

// Copy assignment operator
Cat& Cat::operator=(const Cat& other)
{
    std::cout << "Cat copy assignment operator called" << std::endl;
    if (this != &other)
    {
        AAnimal::operator=(other);
        delete this->brain;
        this->brain = new Brain(*other.brain);
    }
    return *this;
}

// Destructor
Cat::~Cat(void)
{
    std::cout << "Cat destructor called" << std::endl;
    delete this->brain;
}

// Make sound implementation
void Cat::makeSound(void) const
{
    std::cout << "Meow! Meow!" << std::endl;
}

// Get brain
Brain* Cat::getBrain(void) const
{
    return this->brain;
}