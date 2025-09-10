#include "DiamondTrap.hpp"



DiamondTrap::DiamondTrap() 
    : ClapTrap("Albert_clap_name", 100, 50, 30), ScavTrap(), FragTrap(), _name("Albert")
{
    std::cout << "default DiamondTrap constructed" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string& name) 
    : ClapTrap(name + "_clap_name", 100, 50, 30), ScavTrap(), FragTrap(), _name(name)
{
    std::cout << "DiamondTrap " << _name << " constructed" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& src) 
    : ClapTrap(src), ScavTrap(src), FragTrap(src)
{
    _name = src._name;
    std::cout << "DiamondTrap copy constructed" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other)
{
    std::cout << "DiamondTrap copy assignment operator" << std::endl;
    if (this != &other)
    {
        ClapTrap::operator=(other);
        _name = other._name;
    }
    return *this;
}

DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap " << _name << " destroyed" << std::endl;
}

void DiamondTrap::whoAmI()
{
    if (_hitPoints == 0)
    {
        std::cout << "DiamondTrap " << _name << " is dead and cannot identify itself" << std::endl;
        return;
    }
    std::cout << "My name is " << _name << " and my ClapTrap name is " << ClapTrap::_name << std::endl;
}

// DiamondTrap::DiamondTrap() : ClapTrap("Albert_clap_name"), _name("Albert")
// {
//     _hitPoints = FragTrap::_hitPoints;
//     _energyPoints = ScavTrap::_energyPoints;
//     _attackDamage = FragTrap::_attackDamage;
//     std::cout << "default DiamondTrap constructed" << std::endl;
// }

// DiamondTrap::DiamondTrap(const std::string& name) 
//     : ClapTrap(name + "_clap_name"), _name(name)
// {
//     _hitPoints = FragTrap::_hitPoints;
//     _energyPoints = ScavTrap::_energyPoints;
//     _attackDamage = FragTrap::_attackDamage;
//     std::cout << "DiamondTrap " << _name << " constructed" << std::endl;
// }

