# CPP07 Implementation Plan - C++ Templates

## Overview
Module 07 focuses on **C++ function and class templates**. Templates enable writing generic code that works with any data type.

## General Requirements
- Compile with: `c++ -Wall -Wextra -Werror -std=c++98`
- Orthodox Canonical Form for classes (ex02)
- No STL containers/algorithms (until Module 08-09)
- No `using namespace` or `friend` keywords
- Templates must be defined in header files
- Include guards required

---

## Exercise 00: Start with a few functions

### Directory Structure
```
ex00/
├── Makefile
├── main.cpp
└── whatever.hpp
```

### Requirements
Implement three function templates in `whatever.hpp`:

#### 1. `swap<T>`
```cpp
template <typename T>
void swap(T &a, T &b);
```
- Swaps the values of two parameters
- Returns nothing
- Uses a temporary variable for the swap

#### 2. `min<T>`
```cpp
template <typename T>
T const &min(T const &a, T const &b);
```
- Returns the smallest of two values
- **If equal, returns the second one** (important edge case!)
- Returns by const reference

#### 3. `max<T>`
```cpp
template <typename T>
T const &max(T const &a, T const &b);
```
- Returns the greatest of two values
- **If equal, returns the second one** (important edge case!)
- Returns by const reference

### Implementation Notes
- Use `<` operator for comparisons (works for equality case: if `!(a < b)` then return b)
- Templates defined entirely in header file
- Test with `int` and `std::string` as shown in subject

### Expected Output
```
a = 3, b = 2
min(a, b) = 2
max(a, b) = 3
c = chaine2, d = chaine1
min(c, d) = chaine1
max(c, d) = chaine2
```

---

## Exercise 01: Iter

### Directory Structure
```
ex01/
├── Makefile
├── main.cpp
└── iter.hpp
```

### Requirements
Implement an `iter` function template:

```cpp
template <typename T, typename F>
void iter(T *array, size_t length, F func);
```

Parameters:
1. Address of an array (`T *array`)
2. Length of the array (`size_t length` - const value)
3. Function to call on every element (`F func`)

### Implementation Notes

#### Supporting const and non-const arrays
Need two overloads or a careful template design:

```cpp
// For non-const arrays (can modify elements)
template <typename T, typename F>
void iter(T *array, size_t length, F func);

// For const arrays (read-only access)
template <typename T, typename F>
void iter(T const *array, size_t length, F func);
```

Or use a single template that deduces constness automatically.

#### Test Cases to Include
1. Array of `int` with a print function
2. Array of `std::string` with a print function
3. Array of `int` with a modification function (e.g., increment)
4. Const array with a print function (read-only)
5. Using a function template as the third parameter

### Example Test Functions
```cpp
template <typename T>
void print(T const &x) {
    std::cout << x << std::endl;
}

template <typename T>
void increment(T &x) {
    x++;
}
```

---

## Exercise 02: Array

### Directory Structure
```
ex02/
├── Makefile
├── main.cpp
├── Array.hpp
└── Array.tpp (optional - for template implementation)
```

### Requirements
Class template `Array<T>` with Orthodox Canonical Form:

```cpp
template <typename T>
class Array {
private:
    T*              _array;
    unsigned int    _size;

public:
    // Orthodox Canonical Form
    Array();                                // Default constructor
    Array(unsigned int n);                  // Parametric constructor
    Array(Array const &src);                // Copy constructor
    ~Array();                               // Destructor
    Array &operator=(Array const &rhs);     // Assignment operator

    // Member functions
    T &operator[](unsigned int index);              // Subscript operator
    T const &operator[](unsigned int index) const;  // Const subscript operator
    unsigned int size() const;                      // Size getter

    // Exception class
    class OutOfBoundsException : public std::exception {
        const char *what() const throw();
    };
};
```

### Implementation Details

#### Default Constructor
```cpp
Array() : _array(NULL), _size(0) {}
```

#### Parametric Constructor
```cpp
Array(unsigned int n) : _array(new T[n]()), _size(n) {}
```
- Creates array of `n` elements
- Elements initialized by default (value-initialized with `new T[n]()`)
- Note: `new int()` initializes to 0, `new int` leaves uninitialized

#### Copy Constructor (Deep Copy)
```cpp
Array(Array const &src) : _array(NULL), _size(0) {
    *this = src;
}
```

#### Destructor
```cpp
~Array() {
    delete[] _array;
}
```

#### Assignment Operator (Deep Copy)
```cpp
Array &operator=(Array const &rhs) {
    if (this != &rhs) {
        delete[] _array;
        _size = rhs._size;
        _array = new T[_size];
        for (unsigned int i = 0; i < _size; i++)
            _array[i] = rhs._array[i];
    }
    return *this;
}
```

#### Subscript Operator
```cpp
T &operator[](unsigned int index) {
    if (index >= _size)
        throw OutOfBoundsException();
    return _array[index];
}
```
- Need both const and non-const versions
- Throw `std::exception` on out-of-bounds access

#### Size Function
```cpp
unsigned int size() const {
    return _size;
}
```

### Test Cases (from provided main.cpp)
1. Create `Array<int>` with 750 elements
2. Fill with random values
3. Test copy constructor and assignment in nested scope
4. Verify original not affected after copies destroyed
5. Test out-of-bounds access with negative index (-2)
6. Test out-of-bounds access with index == size (MAX_VAL)
7. Modify array elements after tests

### Additional Test Cases to Add
1. Default constructor creates empty array
2. Empty array throws on any access
3. Test with different types (std::string, custom class)
4. Test size() function
5. Const Array access

---

## Makefile Template (for each exercise)

```makefile
NAME        = [program_name]
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

## Implementation Order

1. **ex00** - Simple function templates (swap, min, max)
   - Good introduction to template syntax
   - Focus on return types and const correctness

2. **ex01** - iter function template
   - Practice with function pointers/functors as template parameters
   - Handle const vs non-const arrays

3. **ex02** - Array class template
   - Apply Orthodox Canonical Form to templates
   - Deep copy semantics
   - Exception handling for bounds checking

---

## Key Concepts to Understand

### Template Syntax
```cpp
template <typename T>
T functionName(T param) { ... }
```

### Template Class Definition
```cpp
template <typename T>
class ClassName {
    // Class body
};
```

### Why Templates in Headers?
- Templates are not actual code until instantiated
- Compiler needs full definition at instantiation point
- Cannot separate declaration (.hpp) and definition (.cpp) like regular classes
- Use `.tpp` file included at end of `.hpp` for cleaner organization

### Const Correctness in Templates
- Use `T const &` for parameters that shouldn't be modified
- Provide both const and non-const versions of accessor functions
