#include "Dog.hpp"

Dog::Dog(void) 
    : AAnimal()
{
    std::cout << "Dog default constructor called" << std::endl;
    this->_type = "Dog";
    this->brain = new Brain();
}

Dog::Dog(const Dog& src)
    : AAnimal(src)
{
    std::cout << "Dog copy constructor called" << std::endl;
    this->brain = new Brain(*src.brain);
}

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

Dog::~Dog(void)
{
    std::cout << "Dog destructor called" << std::endl;
    delete this->brain;
}

void Dog::makeSound(void) const
{
    std::cout << "WHO LET THE DOGS OUT" << std::endl;
}

Brain* Dog::getBrain(void) const
{
    return this->brain;
}