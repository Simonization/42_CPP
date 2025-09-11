#include "Brain.hpp"

// Default constructor
Brain::Brain(void)
{
    std::cout << "Brain default constructor called" << std::endl;
    for (int i = 0; i < 100; i++)
        this->ideas[i] = "";
}

// Copy constructor
Brain::Brain(const Brain& src)
{
    std::cout << "Brain copy constructor called" << std::endl;
    for (int i = 0; i < 100; i++)
        this->ideas[i] = src.ideas[i];
}

// Copy assignment operator
Brain& Brain::operator=(const Brain& other)
{
    std::cout << "Brain copy assignment operator called" << std::endl;
    if (this != &other)
    {
        for (int i = 0; i < 100; i++)
            this->ideas[i] = other.ideas[i];
    }
    return *this;
}

// Destructor
Brain::~Brain(void)
{
    std::cout << "Brain destructor called" << std::endl;
}

// Set idea at index
void Brain::setIdea(int index, const std::string& idea)
{
    if (index >= 0 && index < 100)
        this->ideas[index] = idea;
}

// Get idea at index
std::string Brain::getIdea(int index) const
{
    if (index >= 0 && index < 100)
        return this->ideas[index];
    return "";
}