#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap("Albert", 100, 50, 20)
{
		std::cout << "default ScavTrap constructed" << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) :  ClapTrap(name, 100, 50, 20)
{
	std::cout << "ScavTrap " << _name << "constructed" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &src) : ClapTrap(src)
{
	std::cout << "ScavTrap copy constructed" << std::endl;
	*this = src;

}

ScavTrap& ScavTrap::operator=(const ScavTrap &other)
{
	std::cout << "ScavTrap copy assignment operator" << std::endl;
	if(this != &other)
		ClapTrap::operator=(other);
	return *this;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << _name << " destroyed" << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
    if (_hitPoints == 0)
    {
        std::cout << "ScavTrap " << _name << " cannot attack : no hit points left" << std::endl;
        return;
    }
	if (_energyPoints == 0)
    {
        std::cout << "ScavTrap " << _name << " cannot attack : no energy points left" << std::endl;
        return;
    }

    _energyPoints--;
    std::cout << "ScavTrap " << _name << " attacks " << target 
              << ", wreaks " << _attackDamage << " points of damage!!!" << std::endl;
}

void	ScavTrap::guardGate()
{
	if (_hitPoints == 0)
	{
		std::cout << "ScavTrap " << _name << " is dead and cannot enter Gate keeper mode" << std::endl;
		return;
	}
	std::cout << "ScavTrap " << _name << " is now in Gate keeper mode" << std::endl;

}