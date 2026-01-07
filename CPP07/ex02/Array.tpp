#ifndef ARRAY_TPP
# define ARRAY_TPP

template <typename T>
Array<T>::Array(void) : _array(NULL), _size(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n) : _array(NULL), _size(n)
{
	if (n > 0)
		_array = new T[n]();
}

template <typename T>
Array<T>::Array(Array const& src) : _array(NULL), _size(0)
{
	*this = src;
}

template <typename T>
Array<T>::~Array(void)
{
	delete[] _array;
}

template <typename T>
Array<T>&	Array<T>::operator=(Array const& rhs)
{
	if (this != &rhs)
	{
		delete[] _array;
		_size = rhs._size;
		if (_size > 0)
		{
			_array = new T[_size];
			for (unsigned int i = 0; i < _size; i++)
				_array[i] = rhs._array[i];
		}
		else
			_array = NULL;
	}
	return *this;
}

template <typename T>
T&	Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw OutOfBoundsException();
	return _array[index];
}

template <typename T>
T const&	Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw OutOfBoundsException();
	return _array[index];
}

template <typename T>
unsigned int	Array<T>::size(void) const
{
	return _size;
}

template <typename T>
const char*	Array<T>::OutOfBoundsException::what() const throw()
{
	return "Array index out of bounds";
}

#endif
