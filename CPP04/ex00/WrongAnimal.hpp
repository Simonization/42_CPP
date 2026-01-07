#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>
# include <string>

class WrongAnimal
{
protected:
	std::string _type;

public:
	WrongAnimal(void);
	WrongAnimal(const WrongAnimal& src);
	WrongAnimal& operator=(const WrongAnimal& other);
	~WrongAnimal(void);

	void makeSound(void) const;
	std::string getType(void) const;
};

#endif