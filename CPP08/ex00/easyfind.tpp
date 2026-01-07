#ifndef EASYFIND_TPP
# define EASYFIND_TPP

const char* NotFoundException::what(void) const throw()
{
	return "Element not found in container";
}

template <typename T>
typename T::iterator easyfind(T& container, int value)
{
	typename T::iterator it = std::find(container.begin(), container.end(), value);
	if (it == container.end())
		throw NotFoundException();
	return it;
}

#endif
