#include "Cat.hpp"

Cat::Cat(void)
    : Animal()
{
    std::cout << "Cat default constructor called" << std::endl;
    this->_type = "Cat";
    this->brain = new Brain();
}

Cat::Cat(const Cat& src) : Animal(src)
{
    std::cout << "Cat copy constructor called" << std::endl;
    this->brain = new Brain(*src.brain);
}

Cat& Cat::operator=(const Cat& other)
{
    std::cout << "Cat assignment operator called" << std::endl;
    if (this != &other)
    {
        Animal::operator=(other);
        delete this->brain;
        this->brain = new Brain(*other.brain);
    }
    return *this;
}

Cat::~Cat(void)
{
    std::cout << "Cat destructor called" << std::endl;
    delete this->brain;
}

void Cat::makeSound(void) const
{
    std::cout << "Feeling Tense? Have a KitKat" << std::endl;
}

Brain* Cat::getBrain(void) const
{
    return this->brain;
}