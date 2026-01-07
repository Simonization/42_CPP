/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_TPP
# define MUTANTSTACK_TPP

// Orthodox Canonical Form implementations

template <typename T>
MutantStack<T>::MutantStack(void) : std::stack<T>()
{
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack& src) : std::stack<T>(src)
{
}

template <typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack& other)
{
	if (this != &other)
		std::stack<T>::operator=(other);
	return (*this);
}

template <typename T>
MutantStack<T>::~MutantStack(void)
{
}

// Iterator function implementations

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin(void)
{
	return this->c.begin();
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end(void)
{
	return this->c.end();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::begin(void) const
{
	return this->c.begin();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::end(void) const
{
	return this->c.end();
}

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rbegin(void)
{
	return this->c.rbegin();
}

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rend(void)
{
	return this->c.rend();
}

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rbegin(void) const
{
	return this->c.rbegin();
}

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rend(void) const
{
	return this->c.rend();
}

#endif
