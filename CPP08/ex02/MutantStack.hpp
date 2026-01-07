/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
public:
	// Orthodox Canonical Form
	MutantStack(void);
	MutantStack(const MutantStack& src);
	MutantStack& operator=(const MutantStack& other);
	~MutantStack(void);

	// Iterator types (from underlying container)
	typedef typename std::stack<T>::container_type::iterator iterator;
	typedef typename std::stack<T>::container_type::const_iterator const_iterator;
	typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
	typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

	// Iterator functions
	iterator begin(void);
	iterator end(void);
	const_iterator begin(void) const;
	const_iterator end(void) const;
	reverse_iterator rbegin(void);
	reverse_iterator rend(void);
	const_reverse_iterator rbegin(void) const;
	const_reverse_iterator rend(void) const;
};

# include "MutantStack.tpp"

#endif
