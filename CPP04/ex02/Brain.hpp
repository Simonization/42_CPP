#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <string>
# include <iostream>

class Brain
{
private:
    std::string ideas[100];

public:
    // Orthodox Canonical Form
    Brain(void);
    Brain(const Brain& src);
    Brain& operator=(const Brain& other);
    ~Brain(void);

    // Member functions
    void setIdea(int index, const std::string& idea);
    std::string getIdea(int index) const;
};

#endif