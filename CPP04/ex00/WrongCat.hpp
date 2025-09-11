#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

# include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
public:
	WrongCat(void);
	WrongCat(const WrongCat& src);
	WrongCat& operator=(const WrongCat& other);
	~WrongCat(void);  // Note: NOT virtual

	void makeSound(void) const;  // Note: NOT virtual
};

#endif