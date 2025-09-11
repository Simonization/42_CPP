#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	std::cout << "========== Testing correct polymorphism ==========" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	std::cout << std::endl;
	std::cout << j->get_type() << " " << std::endl;
	std::cout << i->get_type() << " " << std::endl;

	i->makeSound();
	j->makeSound();
	meta->makeSound();
	
	std::cout << std::endl;
	delete meta;
	delete j;
	delete i;
	
	std::cout << std::endl;
	std::cout << "========== Testing wrong polymorphism ==========" << std::endl;
	const WrongAnimal* wrongMeta = new WrongAnimal();
	const WrongAnimal* wrongCat = new WrongCat();
	
	std::cout << std::endl;
	std::cout << wrongCat->get_type() << " " << std::endl;

	wrongCat->makeSound();
	wrongMeta->makeSound();
	
	std::cout << std::endl;
	delete wrongMeta;
	delete wrongCat;
	
	std::cout << std::endl;
	std::cout << "========== Additional tests ==========" << std::endl;
	
	//copy constructor
	Dog originalDog;
	Dog copiedDog(originalDog);
	std::cout << "Copied dog _type: " << copiedDog.get_type() << std::endl;
	copiedDog.makeSound();
	
	std::cout << std::endl;
	
	//assignment operator
	Cat cat1;
	Cat cat2;
	cat2 = cat1;
	std::cout << "Assigned cat _type: " << cat2.get_type() << std::endl;
	cat2.makeSound();
	
	std::cout << std::endl;
	
	//direct object calls
	Animal directAnimal;
	Dog directDog;
	Cat directCat;
	
	std::cout << std::endl;
	std::cout << "Direct calls:" << std::endl;
	directAnimal.makeSound();
	directDog.makeSound();
	directCat.makeSound();
	
	std::cout << std::endl;
	
	return 0;
}