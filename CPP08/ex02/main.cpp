/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>
#include <list>

static void testSubject(void)
{
	std::cout << "=== Subject Test (MutantStack) ===" << std::endl;

	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
	std::cout << std::endl;
}

static void testList(void)
{
	std::cout << "=== Comparison Test (std::list) ===" << std::endl;

	std::list<int> lst;
	lst.push_back(5);
	lst.push_back(17);
	std::cout << lst.back() << std::endl;
	lst.pop_back();
	std::cout << lst.size() << std::endl;
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);

	std::list<int>::iterator it = lst.begin();
	std::list<int>::iterator ite = lst.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::cout << std::endl;
}

static void testReverseIterators(void)
{
	std::cout << "=== Reverse Iterator Test ===" << std::endl;

	MutantStack<int> mstack;
	mstack.push(1);
	mstack.push(2);
	mstack.push(3);
	mstack.push(4);
	mstack.push(5);

	std::cout << "Forward: ";
	for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "Reverse: ";
	for (MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit)
		std::cout << *rit << " ";
	std::cout << std::endl << std::endl;
}

static void testConstIterators(void)
{
	std::cout << "=== Const Iterator Test ===" << std::endl;

	MutantStack<int> mstack;
	mstack.push(10);
	mstack.push(20);
	mstack.push(30);

	const MutantStack<int>& constRef = mstack;
	std::cout << "Const forward: ";
	for (MutantStack<int>::const_iterator it = constRef.begin(); it != constRef.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "Const reverse: ";
	for (MutantStack<int>::const_reverse_iterator rit = constRef.rbegin(); rit != constRef.rend(); ++rit)
		std::cout << *rit << " ";
	std::cout << std::endl << std::endl;
}

static void testCopyAndAssignment(void)
{
	std::cout << "=== Copy Constructor & Assignment Test ===" << std::endl;

	MutantStack<int> original;
	original.push(100);
	original.push(200);
	original.push(300);

	// Test copy constructor
	MutantStack<int> copied(original);
	std::cout << "Original: ";
	for (MutantStack<int>::iterator it = original.begin(); it != original.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "Copied: ";
	for (MutantStack<int>::iterator it = copied.begin(); it != copied.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	// Modify original, copied should not change
	original.push(400);
	std::cout << "Original after push(400): ";
	for (MutantStack<int>::iterator it = original.begin(); it != original.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "Copied (unchanged): ";
	for (MutantStack<int>::iterator it = copied.begin(); it != copied.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	// Test assignment operator
	MutantStack<int> assigned;
	assigned.push(999);
	assigned = original;
	std::cout << "Assigned: ";
	for (MutantStack<int>::iterator it = assigned.begin(); it != assigned.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;
}

static void testStackOperations(void)
{
	std::cout << "=== Standard Stack Operations Test ===" << std::endl;

	MutantStack<int> mstack;

	std::cout << "Empty: " << (mstack.empty() ? "true" : "false") << std::endl;
	std::cout << "Size: " << mstack.size() << std::endl;

	mstack.push(42);
	mstack.push(21);

	std::cout << "After pushing 42 and 21:" << std::endl;
	std::cout << "Empty: " << (mstack.empty() ? "true" : "false") << std::endl;
	std::cout << "Size: " << mstack.size() << std::endl;
	std::cout << "Top: " << mstack.top() << std::endl;

	mstack.pop();
	std::cout << "After pop():" << std::endl;
	std::cout << "Size: " << mstack.size() << std::endl;
	std::cout << "Top: " << mstack.top() << std::endl << std::endl;
}

static void testDifferentTypes(void)
{
	std::cout << "=== Different Types Test ===" << std::endl;

	// Test with strings
	MutantStack<std::string> strStack;
	strStack.push("Hello");
	strStack.push("World");
	strStack.push("!");

	std::cout << "String stack: ";
	for (MutantStack<std::string>::iterator it = strStack.begin(); it != strStack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	// Test with doubles
	MutantStack<double> dblStack;
	dblStack.push(1.1);
	dblStack.push(2.2);
	dblStack.push(3.3);

	std::cout << "Double stack: ";
	for (MutantStack<double>::iterator it = dblStack.begin(); it != dblStack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;
}

int main(void)
{
	testSubject();
	testList();
	testReverseIterators();
	testConstIterators();
	testCopyAndAssignment();
	testStackOperations();
	testDifferentTypes();

	return 0;
}
