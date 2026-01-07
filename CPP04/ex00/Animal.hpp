#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

class Animal
{
protected:
	std::string _type;

public:
	Animal(void);
	Animal(const Animal& src);
	Animal& operator=(const Animal& other);
	virtual ~Animal(void);

	virtual void makeSound(void) const;
	std::string getType(void) const;
};

#endif