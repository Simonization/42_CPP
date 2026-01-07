# CPP Correction Guide - Modules 05 to 08

A cheat sheet for your 42 C++ evaluations.

---

## CPP05: Exceptions & Polymorphism

### Main Concepts Learned
- **Custom Exception Classes**: Nested classes inheriting from `std::exception`
- **Virtual Methods & Abstract Classes**: `= 0` pure virtual, virtual destructors
- **Polymorphic Dispatch**: Base pointer calling derived implementations
- **Factory Pattern**: Creating objects dynamically by name (Intern)

### Key Implementation Points

#### Grade System (IMPORTANT - often asked!)
```
Grade 1 = BEST (highest authority)
Grade 150 = WORST (lowest authority)

To sign/execute a form: bureaucrat.grade <= form.requiredGrade
Example: Grade 5 bureaucrat CAN sign a form requiring grade 25
         Grade 50 bureaucrat CANNOT sign a form requiring grade 25
```

#### Exception Pattern
```cpp
class Bureaucrat {
public:
    class GradeTooHighException : public std::exception {
        virtual const char* what() const throw();
    };
};
```
- `throw()` specifier = C++98 way of saying "doesn't throw"
- `what()` returns `const char*` (NOT std::string)

#### Two-Phase Validation in AForm::execute()
1. Check if form is signed → `FormNotSignedException`
2. Check executor's grade → `GradeTooLowException`
3. Call virtual `executeAction()` → polymorphic behavior

#### Intern Factory Pattern
- Uses **function pointer array** + string matching
- Returns `new Form(...)` → **caller must delete**
- No `if/else if/else` chain (clean loop implementation)

### What Evaluators May Ask
- "Why is the grade system inverted?" → Lower number = higher rank
- "What's the difference between Form and AForm?" → AForm is abstract (ex02+)
- "Why virtual destructor in AForm?" → Prevents memory leaks when deleting through base pointer
- "How does Intern avoid long if-else chains?" → Function pointer table/array

### Quick File Reference
| Exercise | Focus | Key Classes |
|----------|-------|-------------|
| ex00 | Basic exceptions | Bureaucrat |
| ex01 | Form interaction | Bureaucrat + Form |
| ex02 | Polymorphism | AForm + 3 concrete forms |
| ex03 | Factory pattern | Intern |

---

## CPP06: C++ Cast Operators

### Main Concepts Learned
- **static_cast**: Compile-time checked numeric conversions
- **reinterpret_cast**: Low-level pointer ↔ integer conversion
- **dynamic_cast**: Runtime type identification (RTTI)

### The Four C++ Casts
| Cast | Safety | When to Use |
|------|--------|-------------|
| `static_cast` | Compile-time | Numeric conversions (int→float) |
| `dynamic_cast` | Runtime | Polymorphic downcasting |
| `reinterpret_cast` | Unsafe | Pointer serialization |
| `const_cast` | N/A | Not used in this module |

### Exercise-Specific Details

#### EX00: ScalarConverter (static_cast)
- **Non-instantiable class**: private constructor/destructor
- Conversion flow: detect type → parse → convert to all 4 types
- Special values: `nan`, `nanf`, `+inf`, `-inf`, `+inff`, `-inff`
- Output format: always 1 decimal place (`42.0f`, `42.0`)

```cpp
// Conversion example
double d = strtod(literal.c_str(), NULL);
int i = static_cast<int>(d);          // static_cast for numeric
char c = static_cast<char>(i);
```

#### EX01: Serializer (reinterpret_cast)
- Converts pointer ↔ `uintptr_t` (guaranteed to hold pointer)
- Round-trip: `serialize(ptr)` → integer → `deserialize()` → same ptr
- **No data modification**, just type reinterpretation

```cpp
uintptr_t serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}
Data* deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
}
```

#### EX02: Base/A/B/C (dynamic_cast)
- **Requires polymorphic class** (virtual destructor in Base)
- Pointer cast: returns `nullptr` on failure
- Reference cast: throws `std::bad_cast` on failure
- **Cannot use `<typeinfo>`** - only dynamic_cast allowed

```cpp
void identify(Base* p) {
    if (dynamic_cast<A*>(p)) std::cout << "A";  // nullptr check
}
void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);              // throws on failure
        std::cout << "A";
    } catch (...) { }
}
```

### What Evaluators May Ask
- "Why is ScalarConverter non-instantiable?" → Utility class, only static methods
- "Why uintptr_t instead of int?" → Guaranteed to hold any pointer on the platform
- "Why can't you use typeid?" → Exercise requirement, forces dynamic_cast usage
- "Difference between pointer and reference dynamic_cast?" → nullptr vs exception

---

## CPP07: Templates

### Main Concepts Learned
- **Function Templates**: Generic functions with `template <typename T>`
- **Class Templates**: Generic classes with member function templates
- **Template Compilation Model**: Code must be in header (or `.tpp`)

### Key Implementation Points

#### EX00: Function Templates (swap, min, max)
```cpp
template <typename T>
const T& min(const T& a, const T& b) {
    return (a < b) ? a : b;  // Uses operator<
}
```
- Return `const T&` to avoid copying
- Type inferred at call site: `min(5, 10)` → `min<int>(5, 10)`

#### EX01: iter() with Multiple Template Parameters
```cpp
template <typename T, typename F>
void iter(T* array, std::size_t len, F func) {
    for (std::size_t i = 0; i < len; i++)
        func(array[i]);
}
```
- `T` = array element type
- `F` = callable type (function pointer or functor)
- Works with any function that takes `T&` or `const T&`

#### EX02: Array Class Template
```cpp
template <typename T>
class Array {
private:
    T* _array;
    unsigned int _size;
public:
    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;  // Both versions!
};
```

**Critical Points:**
- `new T[n]()` → value-initialization (zeros for primitives)
- Deep copy in copy constructor AND assignment operator
- Self-assignment check: `if (this != &rhs)`
- Two versions of `operator[]`: const and non-const

### .hpp vs .tpp Pattern
```cpp
// Array.hpp
template <typename T>
class Array { ... };
#include "Array.tpp"  // Include implementation at end

// Array.tpp
template <typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]()), _size(n) { }
```

### What Evaluators May Ask
- "Why is template code in header?" → Compiler needs full definition at instantiation
- "What's the difference between `.tpp` and `.hpp`?" → Convention only, both are headers
- "Why two versions of operator[]?" → Const objects need const version
- "What does `new T[n]()` do?" → Value-initializes all elements

---

## CPP08: STL Containers & Iterators

### Main Concepts Learned
- **STL Containers**: vector, list, deque, stack
- **Iterators**: Forward, reverse, const variants
- **STL Algorithms**: `std::find`, `std::sort`, `std::min_element`, `std::max_element`
- **Template Member Functions**: Methods that are themselves templates

### Key Implementation Points

#### EX00: easyfind - Container-Agnostic Search
```cpp
template <typename T>
typename T::iterator easyfind(T& container, int value) {
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw NotFoundException();
    return it;
}
```
- `typename T::iterator` → dependent type, needs `typename` keyword
- Works with vector, list, deque (any container with iterators)

#### EX01: Span - Algorithm Usage
```cpp
// shortestSpan: O(n log n) - sort then compare adjacent
std::vector<int> sorted = this->_numbers;  // COPY, not modify original
std::sort(sorted.begin(), sorted.end());
// Compare adjacent pairs...

// longestSpan: O(n) - just find min and max
int min = *std::min_element(_numbers.begin(), _numbers.end());
int max = *std::max_element(_numbers.begin(), _numbers.end());
return max - min;
```

**Range Insertion (template member function):**
```cpp
template <typename Iterator>
void Span::addNumbers(Iterator begin, Iterator end) {
    while (begin != end) {
        addNumber(*begin);  // Reuse single-add for validation
        ++begin;
    }
}
```

#### EX02: MutantStack - Inheriting from STL
```cpp
template <typename T>
class MutantStack : public std::stack<T> {
public:
    typedef typename std::stack<T>::container_type::iterator iterator;

    iterator begin() { return this->c.begin(); }  // 'c' is protected in std::stack
    iterator end()   { return this->c.end(); }
};
```

**Key Insight**: `std::stack` has a protected member `c` (underlying container, default `std::deque`)

### Iterator Types in MutantStack
```cpp
typedef typename std::stack<T>::container_type::iterator iterator;
typedef typename std::stack<T>::container_type::const_iterator const_iterator;
typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;
```

### What Evaluators May Ask
- "Why `typename` before `T::iterator`?" → Dependent type disambiguation
- "Why copy before sorting in shortestSpan?" → Method is const, can't modify original
- "How does MutantStack access the underlying container?" → Protected member `c` via inheritance
- "Why not use `std::stack::container_type` directly?" → To expose iterators while keeping stack interface

### Algorithm Complexity
| Function | Algorithm | Complexity |
|----------|-----------|------------|
| `easyfind` | `std::find` | O(n) |
| `shortestSpan` | Sort + linear | O(n log n) |
| `longestSpan` | min + max | O(n) |

---

## Common Evaluation Topics Across All Modules

### Orthodox Canonical Form (OCF)
Every class needs:
1. Default constructor
2. Copy constructor
3. Copy assignment operator (with self-assignment check!)
4. Destructor

```cpp
Class& operator=(const Class& rhs) {
    if (this != &rhs) {  // CRITICAL: self-assignment check
        // copy members
    }
    return *this;
}
```

### Exception Classes Pattern
```cpp
class MyClass {
public:
    class MyException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Error message";
        }
    };
};
```

### Const Correctness
- Getters should be `const`: `int getX() const;`
- Pass by const reference when not modifying: `void f(const T& x);`
- Const version of operators for const objects

### Memory Management
- `new` → must have matching `delete`
- `new[]` → must have matching `delete[]`
- Factory patterns return ownership → caller deletes

---

## Quick Reference: What's New in Each Module

| Module | New Concepts |
|--------|--------------|
| CPP05 | Exceptions, virtual, abstract classes, factory pattern |
| CPP06 | static_cast, reinterpret_cast, dynamic_cast |
| CPP07 | Function templates, class templates, `.tpp` files |
| CPP08 | STL containers, iterators, algorithms, template inheritance |

---

## Red Flags to Avoid

1. **Memory leaks**: Always pair `new`/`delete`
2. **Missing virtual destructor**: Required for polymorphic base classes
3. **Shallow copy**: Template containers need deep copy
4. **Missing self-assignment check**: `if (this != &rhs)`
5. **Using `typeid`** in CPP06 ex02: Forbidden by subject
6. **if/else chains** in Intern: Use function pointer array
7. **Modifying original in Span**: Sort a copy, method is const
