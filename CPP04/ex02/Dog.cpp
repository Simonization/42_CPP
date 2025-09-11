#include "Dog.hpp"

// Default constructor
Dog::Dog(void) : AAnimal()
{
    std::cout << "Dog default constructor called" << std::endl;
    this->type = "Dog";
    this->brain = new Brain();
}

// Copy constructor
Dog::Dog(const Dog& src) : AAnimal(src)
{
    std::cout << "Dog copy constructor called" << std::endl;
    this->brain = new Brain(*src.brain);
}

// Copy assignment operator
Dog& Dog::operator=(const Dog& other)
{
    std::cout << "Dog copy assignment operator called" << std::endl;
    if (this != &other)
    {
        AAnimal::operator=(other);
        delete this->brain;
        this->brain = new Brain(*other.brain);
    }
    return *this;
}

// Destructor
Dog::~Dog(void)
{
    std::cout << "Dog destructor called" << std::endl;
    delete this->brain;
}

// Make sound implementation
void Dog::makeSound(void) const
{
    std::cout << "Woof! Woof!" << std::endl;
}

// Get brain
Brain* Dog::getBrain(void) const
{
    return this->brain;
}