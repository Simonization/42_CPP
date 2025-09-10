#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
    std::cout << "=== Testing Abstract Class ===" << std::endl;
    
    // This line should NOT compile - AAnimal is abstract
    // AAnimal animal;  // ERROR: Cannot instantiate abstract class
    
    std::cout << "\n=== Creating Dog and Cat ===" << std::endl;
    const AAnimal* dog = new Dog();
    const AAnimal* cat = new Cat();
    
    std::cout << "\n=== Testing polymorphism ===" << std::endl;
    std::cout << "Dog type: " << dog->getType() << std::endl;
    std::cout << "Cat type: " << cat->getType() << std::endl;
    
    dog->makeSound();
    cat->makeSound();
    
    std::cout << "\n=== Testing array of animals ===" << std::endl;
    const int arraySize = 4;
    AAnimal* animals[arraySize];
    
    // Create half dogs, half cats
    for (int i = 0; i < arraySize / 2; i++)
        animals[i] = new Dog();
    for (int i = arraySize / 2; i < arraySize; i++)
        animals[i] = new Cat();
    
    std::cout << "\n=== Making all animals sound ===" << std::endl;
    for (int i = 0; i < arraySize; i++)
        animals[i]->makeSound();
    
    std::cout << "\n=== Testing deep copy ===" << std::endl;
    Dog originalDog;
    originalDog.getBrain()->setIdea(0, "I want a bone!");
    
    Dog copiedDog(originalDog);  // Copy constructor
    std::cout << "Original dog's idea: " << originalDog.getBrain()->getIdea(0) << std::endl;
    std::cout << "Copied dog's idea: " << copiedDog.getBrain()->getIdea(0) << std::endl;
    
    copiedDog.getBrain()->setIdea(0, "I want to play!");
    std::cout << "After modification:" << std::endl;
    std::cout << "Original dog's idea: " << originalDog.getBrain()->getIdea(0) << std::endl;
    std::cout << "Copied dog's idea: " << copiedDog.getBrain()->getIdea(0) << std::endl;
    
    std::cout << "\n=== Cleanup ===" << std::endl;
    delete dog;
    delete cat;
    
    for (int i = 0; i < arraySize; i++)
        delete animals[i];
    
    return 0;
}