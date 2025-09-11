#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>
# include <string>

class WrongAnimal
{
protected:
	std::string type;

public:
	WrongAnimal(void);
	WrongAnimal(const WrongAnimal& src);
	WrongAnimal& operator=(const WrongAnimal& other);
	~WrongAnimal(void);  // Note: NOT virtual

	void makeSound(void) const;  // Note: NOT virtual
	std::string getType(void) const;
};

#endif