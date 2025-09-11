#ifndef DOG_HPP
# define DOG_HPP

# include "AAnimal.hpp"
# include "Brain.hpp"

class Dog : public AAnimal
{
private:
    Brain* brain;

public:
    // Orthodox Canonical Form
    Dog(void);
    Dog(const Dog& src);
    Dog& operator=(const Dog& other);
    virtual ~Dog(void);

    // Member functions
    virtual void makeSound(void) const;
    Brain* getBrain(void) const;
};

#endif