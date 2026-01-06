#include "Zombie.hpp"

int	main(void)
{
	std::cout << "Creating zombie on the heap:" << std::endl;
	Zombie*	heapZombie = newZombie("HeapZombie");
	heapZombie->announce();
	
	std::cout << std::endl << "Creating zombie on the stack:" << std::endl;
	randomChump("StackZombie");
	
	std::cout << std::endl << "Creating another stack zombie directly:" << std::endl;
	{
		Zombie	directStackZombie("DirectStackZombie");
		directStackZombie.announce();
	}
	std::cout << "DirectStackZombie destroyed" << std::endl;
	
	std::cout << std::endl << "Deleting heap zombie:" << std::endl;
	delete heapZombie;
	
	return (0);
}