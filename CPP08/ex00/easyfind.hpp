#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <exception>

class NotFoundException : public std::exception
{
public:
	virtual const char* what(void) const throw();
};

template <typename T>
typename T::iterator easyfind(T& container, int value);

# include "easyfind.tpp"

#endif
