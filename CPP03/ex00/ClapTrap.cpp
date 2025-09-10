#include "ClapTrap.hpp"

ClapTrap::ClapTrap(): _name("Albert"), _hitPoints(10),  _energyPoints(10), _attackDamage(0)
{
	std::cout << "default ClapTrap " << _name << " constructed" << std::endl;
}

ClapTrap::ClapTrap (const std::string &name) :	_name(name), _hitPoints(10),  _energyPoints(10), _attackDamage(0)	{
	//this->_name = name;
	//this->_hitPoints = 10;
	//this->_energyPoints = 10;
	//this->_attackDamage = 0;
	std::cout << "ClapTrap " << _name << " constructed" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other)
{
	std::cout << "copy constructor" << std::endl;
	*this = other;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
	std::cout << "ClapTrap copy assignment operator called" << std::endl;
	if(this != &other)
	{
		this->_name = other._name;
		this->_hitPoints = other._hitPoints;
		this->_energyPoints = other._energyPoints;
		this->_attackDamage = other._attackDamage;
	}
	return *this;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << _name << " destroyed" << std::endl;
}


void	ClapTrap::attack(const std::string &target)
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " cannot attack : no hit points left" << std::endl;
		return;
	}
	if (_energyPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " cannot attack : no energy points left" << std::endl;
		return;
	}
	
	_energyPoints--;
	std::cout << "ClapTrap " << _name << " attacks " << target 
				<< ", wreaks " << _attackDamage << " points of damage!!!" << std::endl;	
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " is already dead" << std::endl;
		return;
	}
	if (amount >= _hitPoints)
	{
		_hitPoints = 0;
		std::cout << "ClapTrap " << _name << " takes " << amount 
					<< " damage and dies!" << std::endl;
	}
	else
	{
		_hitPoints -= amount;
		std::cout << "ClapTrap " << _name << " takes " << amount 
					<< " damage! Hit points remaining: " << _hitPoints << std::endl;
	}
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " cannot repair : no hit points left" << std::endl;
		return;
	}
	if (_energyPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " cannot repair : no energy points left" << std::endl;
		return;
	}
	
	_energyPoints--;
	_hitPoints += amount;
	std::cout << "ClapTrap " << _name << " repairs itself for " << amount
				<< " hit points. Current hit points: " << _hitPoints << std::endl; 
}
