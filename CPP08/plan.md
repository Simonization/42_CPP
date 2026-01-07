# CPP08 Implementation Plan

## Overview
Module 08 focuses on **Templated containers, iterators, and algorithms** using the STL.
This module allows (and requires) use of STL containers and `<algorithm>`.

---

## Code Style Reference (from CPP01-CPP05)

### Header Files (.hpp)
```cpp
#ifndef CLASSNAME_HPP
# define CLASSNAME_HPP

# include <iostream>

class ClassName
{
private:
    Type    _member;

public:
    ClassName(void);
    ClassName(const ClassName& src);
    ClassName& operator=(const ClassName& other);
    ~ClassName(void);
};

#endif
```

### Naming Conventions
- **Classes**: PascalCase (`Span`, `MutantStack`)
- **Member variables**: `_prefixedWithUnderscore`
- **Methods**: camelCase (`addNumber`, `shortestSpan`)
- **Constants**: UPPERCASE_WITH_UNDERSCORES

### Orthodox Canonical Form (OCF)
All classes must implement:
1. Default constructor
2. Copy constructor
3. Assignment operator (with self-assignment check)
4. Destructor

### Makefile Template
```makefile
NAME        = program_name
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98

SRCS        = main.cpp
OBJS        = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

---

## Exercise 00: Easy find

### Directory: `ex00/`

### Files to Create
| File | Description |
|------|-------------|
| `Makefile` | Build system |
| `easyfind.hpp` | Template function declaration & implementation |
| `main.cpp` | Test cases |

### Requirements
- Template function `easyfind<T>` that takes:
  - Parameter 1: Container of type `T` (contains integers)
  - Parameter 2: An integer to find
- Returns iterator to first occurrence
- Throws exception if not found
- No associative containers support needed

### Implementation Steps

#### Step 1: Create `easyfind.hpp`
```cpp
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

# include "easyfind.tpp"  // Optional: implementation in .tpp

#endif
```

#### Step 2: Implement template function
- Use `std::find()` from `<algorithm>`
- Return iterator if found
- Throw `NotFoundException` if `std::find` returns `container.end()`

```cpp
template <typename T>
typename T::iterator easyfind(T& container, int value)
{
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw NotFoundException();
    return it;
}
```

#### Step 3: Create `main.cpp` with tests
Test with multiple container types:
- `std::vector<int>`
- `std::list<int>`
- `std::deque<int>`

Test cases:
1. Find existing element (first, middle, last)
2. Find non-existing element (expect exception)
3. Search in empty container
4. Container with duplicates (should return first occurrence)

#### Step 4: Create `Makefile`
- NAME = easyfind
- SRCS = main.cpp
- Standard flags: `-Wall -Wextra -Werror -std=c++98`

---

## Exercise 01: Span

### Directory: `ex01/`

### Files to Create
| File | Description |
|------|-------------|
| `Makefile` | Build system |
| `Span.hpp` | Class declaration |
| `Span.cpp` | Class implementation |
| `main.cpp` | Test cases |

### Requirements
- Store maximum of N integers (N = unsigned int, constructor param)
- `addNumber(int)`: Add single number, throw if full
- `shortestSpan()`: Return smallest difference between any two numbers
- `longestSpan()`: Return largest difference between any two numbers
- Throw exception if < 2 numbers stored
- **Bonus**: Add range of numbers via iterator range

### Class Design

```cpp
class Span
{
private:
    unsigned int        _maxSize;
    std::vector<int>    _numbers;

public:
    // Orthodox Canonical Form
    Span(void);
    Span(unsigned int n);
    Span(const Span& src);
    Span& operator=(const Span& other);
    ~Span(void);

    // Member functions
    void addNumber(int number);
    unsigned int shortestSpan(void) const;
    unsigned int longestSpan(void) const;

    // Range insertion (template)
    template <typename Iterator>
    void addNumbers(Iterator begin, Iterator end);

    // Nested exceptions
    class SpanFullException : public std::exception
    {
    public:
        virtual const char* what(void) const throw();
    };

    class NoSpanException : public std::exception
    {
    public:
        virtual const char* what(void) const throw();
    };
};
```

### Implementation Steps

#### Step 1: Create `Span.hpp`
- Include guards
- Include `<vector>`, `<algorithm>`, `<exception>`
- Declare class with OCF + member functions
- Declare nested exception classes

#### Step 2: Create `Span.cpp`
Implement:

1. **Constructors**
   - Default: `_maxSize(0)`
   - Parameterized: `_maxSize(n)`, reserve vector space
   - Copy: Deep copy of vector

2. **addNumber(int)**
   ```cpp
   void Span::addNumber(int number)
   {
       if (this->_numbers.size() >= this->_maxSize)
           throw SpanFullException();
       this->_numbers.push_back(number);
   }
   ```

3. **shortestSpan()**
   - Check size >= 2
   - Sort a copy of the vector
   - Find minimum adjacent difference using `std::adjacent_difference` or manual loop
   ```cpp
   unsigned int Span::shortestSpan(void) const
   {
       if (this->_numbers.size() < 2)
           throw NoSpanException();
       std::vector<int> sorted = this->_numbers;
       std::sort(sorted.begin(), sorted.end());
       unsigned int minSpan = static_cast<unsigned int>(sorted[1] - sorted[0]);
       for (size_t i = 2; i < sorted.size(); i++)
       {
           unsigned int diff = static_cast<unsigned int>(sorted[i] - sorted[i - 1]);
           if (diff < minSpan)
               minSpan = diff;
       }
       return minSpan;
   }
   ```

4. **longestSpan()**
   - Check size >= 2
   - Use `std::min_element` and `std::max_element`
   ```cpp
   unsigned int Span::longestSpan(void) const
   {
       if (this->_numbers.size() < 2)
           throw NoSpanException();
       int min = *std::min_element(this->_numbers.begin(), this->_numbers.end());
       int max = *std::max_element(this->_numbers.begin(), this->_numbers.end());
       return static_cast<unsigned int>(max - min);
   }
   ```

5. **addNumbers(Iterator, Iterator)** - Template in header
   ```cpp
   template <typename Iterator>
   void Span::addNumbers(Iterator begin, Iterator end)
   {
       while (begin != end)
       {
           this->addNumber(*begin);
           ++begin;
       }
   }
   ```

#### Step 3: Create `main.cpp` with tests

**Required test (from subject):**
```cpp
int main()
{
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp.shortestSpan() << std::endl;  // Expected: 2
    std::cout << sp.longestSpan() << std::endl;   // Expected: 14
    return 0;
}
```

**Additional tests:**
1. Test with 10,000+ numbers
2. Test exceptions (span full, no span possible)
3. Test range insertion with iterators
4. Test copy constructor and assignment operator
5. Edge cases: negative numbers, duplicates, INT_MIN/INT_MAX

#### Step 4: Create `Makefile`
- NAME = span
- SRCS = main.cpp Span.cpp

---

## Exercise 02: Mutated abomination

### Directory: `ex02/`

### Files to Create
| File | Description |
|------|-------------|
| `Makefile` | Build system |
| `MutantStack.hpp` | Template class declaration & implementation |
| `main.cpp` | Test cases |

### Requirements
- Inherit from `std::stack`
- Provide all `std::stack` member functions
- Add iterator support (`begin()`, `end()`, `rbegin()`, `rend()`)
- Output should match `std::list` with equivalent operations

### Key Insight
`std::stack` uses a protected member `c` (the underlying container, default `std::deque`).
We can expose its iterators.

### Class Design

```cpp
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

# include "MutantStack.tpp"  // Optional

#endif
```

### Implementation Steps

#### Step 1: Create `MutantStack.hpp`
- Include `<stack>`
- Template class inheriting from `std::stack<T>`
- Define iterator typedefs using underlying container
- Declare OCF + iterator member functions

#### Step 2: Implement template methods

```cpp
template <typename T>
MutantStack<T>::MutantStack(void) : std::stack<T>() {}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack& src) : std::stack<T>(src) {}

template <typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack& other)
{
    if (this != &other)
        std::stack<T>::operator=(other);
    return (*this);
}

template <typename T>
MutantStack<T>::~MutantStack(void) {}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin(void)
{
    return this->c.begin();  // 'c' is the protected underlying container
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end(void)
{
    return this->c.end();
}

// ... similar for const and reverse iterators
```

#### Step 3: Create `main.cpp` with tests

**Required test (from subject):**
```cpp
int main()
{
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
    return 0;
}
```

**Comparison test with std::list:**
```cpp
void testWithList()
{
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
}
```

**Additional tests:**
1. Reverse iterators
2. Const iterators
3. Copy constructor and assignment
4. Different element types (not just int)
5. Standard stack operations (push, pop, top, size, empty)

#### Step 4: Create `Makefile`
- NAME = mutantstack
- SRCS = main.cpp

---

## File Structure Summary

```
CPP08/
├── plan.md
├── ex00/
│   ├── Makefile
│   ├── easyfind.hpp
│   ├── easyfind.tpp (optional)
│   └── main.cpp
├── ex01/
│   ├── Makefile
│   ├── Span.hpp
│   ├── Span.cpp
│   └── main.cpp
└── ex02/
    ├── Makefile
    ├── MutantStack.hpp
    ├── MutantStack.tpp (optional)
    └── main.cpp
```

---

## Implementation Order

### Phase 1: ex00 (Easy find)
1. Create directory structure
2. Write `easyfind.hpp` with NotFoundException class
3. Implement template function using `std::find`
4. Write comprehensive `main.cpp` tests
5. Create Makefile
6. Compile and test with `-std=c++98`

### Phase 2: ex01 (Span)
1. Create directory structure
2. Write `Span.hpp` with class declaration
3. Implement `Span.cpp`:
   - OCF methods
   - `addNumber()`
   - `shortestSpan()` using sort + adjacent difference
   - `longestSpan()` using min/max elements
4. Add template `addNumbers()` in header
5. Write `main.cpp` with subject test + 10,000+ number test
6. Create Makefile
7. Compile and test

### Phase 3: ex02 (MutantStack)
1. Create directory structure
2. Write `MutantStack.hpp`:
   - Inherit from `std::stack<T>`
   - Define iterator typedefs from `container_type`
   - Implement iterator access via `this->c`
3. Write `main.cpp` with subject test
4. Add comparison test with `std::list`
5. Create Makefile
6. Compile and test

---

## Testing Checklist

### ex00
- [ ] Find first element in vector
- [ ] Find middle element in list
- [ ] Find last element in deque
- [ ] Exception on not found
- [ ] Empty container handling
- [ ] First occurrence with duplicates

### ex01
- [ ] Subject test outputs 2 and 14
- [ ] 10,000+ numbers test
- [ ] SpanFullException thrown
- [ ] NoSpanException with 0 elements
- [ ] NoSpanException with 1 element
- [ ] Range insertion works
- [ ] Copy constructor deep copies
- [ ] Assignment operator works
- [ ] Negative numbers handled
- [ ] Duplicate numbers handled

### ex02
- [ ] Subject test matches expected output
- [ ] Output matches std::list equivalent
- [ ] All stack operations work (push, pop, top, size, empty)
- [ ] begin() and end() work
- [ ] rbegin() and rend() work
- [ ] const iterators work
- [ ] Copy constructor works
- [ ] Assignment operator works
- [ ] Can construct std::stack from MutantStack

---

## Common Pitfalls to Avoid

1. **Forgetting C++98 compliance**: No `auto`, no range-based for, no `nullptr`
2. **Integer overflow in span**: Use unsigned int for differences
3. **Iterator invalidation**: Be careful with vector modifications
4. **Missing const correctness**: Span methods should be const where applicable
5. **Not using STL algorithms**: Subject requires use of `<algorithm>` where appropriate
6. **Forgetting self-assignment check**: In assignment operators
7. **Memory leaks**: Though unlikely with STL containers, be mindful
