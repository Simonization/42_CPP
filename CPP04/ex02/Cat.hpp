#ifndef CAT_HPP
# define CAT_HPP

# include "AAnimal.hpp"
# include "Brain.hpp"

class Cat : public AAnimal
{
private:
    Brain* brain;

public:
    // Orthodox Canonical Form
    Cat(void);
    Cat(const Cat& src);
    Cat& operator=(const Cat& rhs);
    virtual ~Cat(void);

    // Member functions
    virtual void makeSound(void) const;
    Brain* getBrain(void) const;
};

#endif