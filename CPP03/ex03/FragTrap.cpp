#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap("Albert", 100, 100, 30)
{
    std::cout << "default FragTrap constructed" << std::endl;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name, 100, 100, 30)
{
    std::cout << "FragTrap " << _name << " constructed" << std::endl;
}

FragTrap::FragTrap(const FragTrap &src) : ClapTrap(src)
{
    std::cout << "FragTrap copy constructed" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap &other)
{
    std::cout << "FragTrap copy assignment operator" << std::endl;
    if (this != &other)
        ClapTrap::operator=(other);
    return *this;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap " << _name << " destroyed" << std::endl;
}

void FragTrap::highFivesGuys(void)
{
    if (_hitPoints == 0)
    {
        std::cout << "FragTrap " << _name << " is dead and cannot request high fives" << std::endl;
        return;
    }
    std::cout << "FragTrap " << _name << " requests a positive high five! ✋" << std::endl;
}