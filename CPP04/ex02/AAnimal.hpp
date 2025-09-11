#ifndef AANIMAL_HPP
# define AANIMAL_HPP

# include <iostream>
# include <string>

class AAnimal
{
protected:
    std::string _type;

public:
    AAnimal(void);
    AAnimal(const AAnimal& src);
    AAnimal& operator=(const AAnimal& other);
    virtual ~AAnimal(void);

    virtual void makeSound(void) const = 0;
    std::string get_type(void) const;
};

#endif