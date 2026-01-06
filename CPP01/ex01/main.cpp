#include "Zombie.hpp"

int	main(void)
{
	int	N = 5;
	std::string name = "Bob";
	
	std::cout << "========================================" << std::endl;
	std::cout << "Creating a horde of " << N << " zombies named " << name << std::endl;
	std::cout << "========================================" << std::endl;
	
	Zombie*	horde = zombieHorde(N, name);
	
	std::cout << "\n--- Zombies announcing themselves ---" << std::endl;
	for (int i = 0; i < N; i++)
	{
		std::cout << "Zombie [" << i << "]: ";
		horde[i].announce();
	}
	
	std::cout << "\n========================================" << std::endl;
	std::cout << "Destroying the horde..." << std::endl;
	std::cout << "========================================" << std::endl;
	delete [] horde;
	
	std::cout << "\n========================================" << std::endl;
	std::cout << "Testing with different horde sizes" << std::endl;
	std::cout << "========================================" << std::endl;
	
	std::cout << "\n--- Creating horde of 1 zombie ---" << std::endl;
	Zombie* singleZombie = zombieHorde(1, "Solo");
	singleZombie[0].announce();
	delete [] singleZombie;
	
	std::cout << "\n--- Creating horde of 10 zombies ---" << std::endl;
	Zombie* bigHorde = zombieHorde(10, "Legion");
	for (int i = 0; i < 10; i++)
	{
		if (i == 0 || i == 4 || i == 9)
		{
			std::cout << "Zombie [" << i << "]: ";
			bigHorde[i].announce();
		}
	}
	delete [] bigHorde;
	
	std::cout << "\n--- Testing with invalid N (0) ---" << std::endl;
	Zombie* invalidHorde = zombieHorde(0, "Invalid");
	if (invalidHorde == NULL)
		std::cout << "Correctly returned NULL for N = 0" << std::endl;
	
	std::cout << "\n--- Testing with invalid N (-5) ---" << std::endl;
	invalidHorde = zombieHorde(-5, "Invalid");
	if (invalidHorde == NULL)
		std::cout << "Correctly returned NULL for N = -5" << std::endl;
	
	std::cout << "\n========================================" << std::endl;
	std::cout << "All tests completed successfully!" << std::endl;
	std::cout << "========================================" << std::endl;
	
	return (0);
}