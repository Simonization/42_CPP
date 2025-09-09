#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
    std::cout << "=== TEST 1: Basic test from subject ===" << std::endl;
    {
        const Animal* j = new Dog();
        const Animal* i = new Cat();
        
        delete j; // should not create a leak
        delete i;
    }
    
    std::cout << "\n=== TEST 2: Array of Animals ===" << std::endl;
    {
        const int arraySize = 10;
        Animal* animals[arraySize];
        
        std::cout << "Creating animals..." << std::endl;
        for (int i = 0; i < arraySize; i++)
        {
            if (i < arraySize / 2)
                animals[i] = new Dog();
            else
                animals[i] = new Cat();
        }
        
        std::cout << "\nTesting sounds..." << std::endl;
        for (int i = 0; i < arraySize; i++)
        {
            animals[i]->makeSound();
        }
        
        std::cout << "\nDeleting animals..." << std::endl;
        for (int i = 0; i < arraySize; i++)
        {
            delete animals[i];
        }
    }
    
    std::cout << "\n=== TEST 3: Deep Copy Test ===" << std::endl;
    {
        std::cout << "Creating original Dog" << std::endl;
        Dog originalDog;
        originalDog.getBrain()->ideas[0] = "I want to play!";
        originalDog.getBrain()->ideas[1] = "I love my human!";
        
        std::cout << "\nCreating copy using copy constructor" << std::endl;
        Dog copiedDog(originalDog);
        
        std::cout << "\nOriginal dog's first idea: " << originalDog.getBrain()->ideas[0] << std::endl;
        std::cout << "Copied dog's first idea: " << copiedDog.getBrain()->ideas[0] << std::endl;
        
        std::cout << "\nChanging copied dog's idea..." << std::endl;
        copiedDog.getBrain()->ideas[0] = "I want to sleep!";
        
        std::cout << "Original dog's first idea: " << originalDog.getBrain()->ideas[0] << std::endl;
        std::cout << "Copied dog's first idea: " << copiedDog.getBrain()->ideas[0] << std::endl;
        
        std::cout << "\nBrain addresses:" << std::endl;
        std::cout << "Original dog's brain: " << originalDog.getBrain() << std::endl;
        std::cout << "Copied dog's brain: " << copiedDog.getBrain() << std::endl;
        
        if (originalDog.getBrain() != copiedDog.getBrain())
            std::cout << "✓ Deep copy successful - different brain addresses!" << std::endl;
        else
            std::cout << "✗ Shallow copy detected - same brain addresses!" << std::endl;
    }
    
    std::cout << "\n=== TEST 4: Assignment Operator Test ===" << std::endl;
    {
        std::cout << "Creating two cats" << std::endl;
        Cat cat1;
        Cat cat2;
        
        cat1.getBrain()->ideas[0] = "I want tuna!";
        cat2.getBrain()->ideas[0] = "I want to nap!";
        
        std::cout << "\nBefore assignment:" << std::endl;
        std::cout << "Cat1's idea: " << cat1.getBrain()->ideas[0] << std::endl;
        std::cout << "Cat2's idea: " << cat2.getBrain()->ideas[0] << std::endl;
        
        std::cout << "\nPerforming assignment cat2 = cat1" << std::endl;
        cat2 = cat1;
        
        std::cout << "\nAfter assignment:" << std::endl;
        std::cout << "Cat1's idea: " << cat1.getBrain()->ideas[0] << std::endl;
        std::cout << "Cat2's idea: " << cat2.getBrain()->ideas[0] << std::endl;
        
        std::cout << "\nChanging cat2's idea..." << std::endl;
        cat2.getBrain()->ideas[0] = "I changed my mind!";
        
        std::cout << "Cat1's idea: " << cat1.getBrain()->ideas[0] << std::endl;
        std::cout << "Cat2's idea: " << cat2.getBrain()->ideas[0] << std::endl;
        
        if (cat1.getBrain() != cat2.getBrain())
            std::cout << "✓ Deep copy successful - different brain addresses!" << std::endl;
        else
            std::cout << "✗ Shallow copy detected - same brain addresses!" << std::endl;
    }
    
    std::cout << "\n=== TEST 5: Polymorphic Deletion ===" << std::endl;
    {
        Animal* polyDog = new Dog();
        Animal* polyCat = new Cat();
        
        polyDog->makeSound();
        polyCat->makeSound();
        
        std::cout << "\nDeleting through Animal pointers..." << std::endl;
        delete polyDog;
        delete polyCat;
        std::cout << "✓ Proper destructor chain called!" << std::endl;
    }
    
    std::cout << "\n=== All tests completed ===" << std::endl;
    
    return 0;
}