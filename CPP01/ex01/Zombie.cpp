#include "Zombie.hpp"

Zombie::Zombie(void)
{
	std::cout << "Zombie created" << std::endl;
}

Zombie::Zombie(std::string name) : _name(name)
{
	std::cout << this->_name << " is born!" << std::endl;
}

Zombie::~Zombie(void)
{
	std::cout << this->_name << " is destroyed!" << std::endl;
}

void	Zombie::announce(void) const
{
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::setName(std::string name)
{
	this->_name = name;
}