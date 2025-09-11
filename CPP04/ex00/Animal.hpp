// #ifndef ANIMAL_HPP
// # define ANIMAL_HPP

// #include <iostream>

// class Animal
// {
// private
// 	std::string	_type;
// public
	
// 	void	makeSound(const std::string &animalSound);
// };

// #endif


#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

class Animal
{
protected:
	std::string type;

public:
	Animal(void);
	Animal(const Animal& src);
	Animal& operator=(const Animal& other);
	virtual ~Animal(void);

	virtual void makeSound(void) const;
	std::string getType(void) const;
};

#endif