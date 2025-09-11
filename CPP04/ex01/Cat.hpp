#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
private:
    Brain* brain;

public:
    Cat(void);
    Cat(const Cat &src);
    Cat &operator=(const Cat &other);
    virtual ~Cat(void);

    virtual void makeSound(void) const;
    Brain* getBrain(void) const;
};

#endif