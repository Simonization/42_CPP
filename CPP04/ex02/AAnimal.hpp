#ifndef AANIMAL_HPP
# define AANIMAL_HPP

# include <string>
# include <iostream>

class AAnimal
{
protected:
    std::string type;

public:
    // Orthodox Canonical Form
    AAnimal(void);                                // Default constructor
    AAnimal(const AAnimal& src);                  // Copy constructor
    AAnimal& operator=(const AAnimal& rhs);       // Copy assignment operator
    virtual ~AAnimal(void);                       // Virtual destructor

    // Member functions
    virtual void makeSound(void) const = 0;       // Pure virtual function - makes class abstract
    std::string getType(void) const;
};

#endif