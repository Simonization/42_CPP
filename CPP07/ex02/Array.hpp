#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <exception>
# include <cstddef>

template <typename T>
class Array
{
public:
	Array(void);
	Array(unsigned int n);
	Array(const Array& src);
	~Array(void);

	Array&	operator=(const Array& rhs);
	T&		operator[](unsigned int index);
	const T&	operator[](unsigned int index) const;

	unsigned int	size(void) const;

	class OutOfBoundsException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

private:
	T*				_array;
	unsigned int	_size;
};

# include "Array.tpp"

#endif
