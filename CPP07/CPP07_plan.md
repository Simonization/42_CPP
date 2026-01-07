# CPP07 - C++ Templates - Tutor Review

## Project Structure Overview

```
CPP07/
├── ex00/          (whatever - swap, min, max templates)
│   ├── Makefile
│   ├── main.cpp
│   └── whatever.hpp
├── ex01/          (iter - function template with arrays)
│   ├── Makefile
│   ├── main.cpp
│   └── iter.hpp
└── ex02/          (Array - class template)
    ├── Makefile
    ├── main.cpp
    ├── Array.hpp
    └── Array.tpp
```

---

## Ex00: Start here (whatever) - REVIEW

### Requirements Check
| Requirement | Status | Notes |
|-------------|--------|-------|
| swap template function | ✅ | Works correctly |
| min template function | ✅ | Returns second if equal |
| max template function | ✅ | Returns second if equal |
| Works with any comparable type | ✅ | Tested with int, string |

### Code Quality
- **Good**: Const references used appropriately in min/max
- **Good**: Simple and readable implementation
- **Good**: Subject's example main used (exact expected output)

### Potential Discussion Points
- None - implementation is clean and correct

### Verdict: ✅ PASS

---

## Ex01: Iter - REVIEW

### Requirements Check
| Requirement | Status | Notes |
|-------------|--------|-------|
| iter function template | ✅ | Implemented |
| Takes array, length, function | ✅ | All parameters present |
| Works with any type | ✅ | Tested multiple types |
| Can call instantiated function templates | ✅ | print<int> etc. work |

### Code Quality
- **Good**: Uses two template parameters (T for array, F for function)
- **Good**: Comprehensive test cases
- **Good**: Tests const arrays, different types

### Potential Discussion Points
⚠️ **Question for evaluation**: The iter function uses `template <typename T, typename F>`. Some evaluators may expect a more restrictive signature like:
```cpp
template <typename T>
void iter(T* array, size_t len, void (*func)(T&));
```
However, using two template parameters is **more flexible** and **acceptable** as it allows:
- Function pointers
- Function objects
- Lambda expressions (C++11)

The current implementation is actually superior but may need justification during evaluation.

### Verdict: ✅ PASS (be prepared to justify the dual template approach)

---

## Ex02: Array - REVIEW

### Requirements Check
| Requirement | Status | Notes |
|-------------|--------|-------|
| Default constructor (empty array) | ✅ | Creates array with size 0 |
| Constructor with unsigned int n | ✅ | Default-initializes elements |
| Copy constructor (deep copy) | ✅ | Works correctly |
| Assignment operator (deep copy) | ✅ | Works correctly |
| Destructor | ✅ | Properly deletes array |
| operator[] | ✅ | Both const and non-const versions |
| size() member function | ✅ | Returns unsigned int |
| Exception on invalid access | ✅ | Throws std::exception derived |

### Orthodox Canonical Form
| Element | Status |
|---------|--------|
| Default constructor | ✅ |
| Copy constructor | ✅ |
| Assignment operator | ✅ |
| Destructor | ✅ |

### Code Quality Issues

#### 1. Copy Constructor Pattern (Minor)
```cpp
Array<T>::Array(Array const& src) : _array(NULL), _size(0)
{
    *this = src;  // Delegates to operator=
}
```
**Observation**: This works but is not the cleanest pattern. The copy constructor calls operator= which:
- First deletes NULL (safe but unnecessary)
- Then allocates new memory

**Not a bug**, but some evaluators might prefer direct initialization.

#### 2. Exception Safety (Minor - Advanced Topic)
```cpp
Array<T>&	Array<T>::operator=(Array const& rhs)
{
    if (this != &rhs)
    {
        delete[] _array;        // Memory freed
        _size = rhs._size;
        if (_size > 0)
            _array = new T[_size];  // If this throws...
```
If `new` throws `std::bad_alloc`, the object is left in an invalid state (_array is dangling, old memory already freed).

**Better pattern** (for discussion only - current code is acceptable for 42):
```cpp
T* temp = new T[rhs._size];  // Allocate first
delete[] _array;              // Delete only if allocation succeeded
_array = temp;
```

This is an **advanced topic** and the current implementation is acceptable for CPP07.

#### 3. Default Initialization
```cpp
_array = new T[n]();  // Note the ()
```
**Good**: The `()` ensures value-initialization (zeros for built-in types).

### Test Coverage
- ✅ Empty array
- ✅ Sized array
- ✅ Copy constructor
- ✅ Assignment operator
- ✅ Out of bounds access
- ✅ String array
- ✅ Const array access
- ✅ Large array (subject test)
- ✅ Self-assignment
- ✅ Negative index (wraps to large unsigned)

### Verdict: ✅ PASS

---

## Summary

| Exercise | Status | Comments |
|----------|--------|----------|
| ex00 | ✅ PASS | Clean implementation |
| ex01 | ✅ PASS | Dual template params - justify if asked |
| ex02 | ✅ PASS | Minor exception safety discussion possible |

## Compilation Check
All exercises compile with `-Wall -Wextra -Werror -std=c++98` without warnings.

## Memory Leaks
Run `make leak` in each directory to verify with Valgrind.

---

## Questions to Expect During Evaluation

1. **Ex00**: "Why do min/max return the second argument when equal?"
   - Subject requirement for consistent behavior when comparing equal values

2. **Ex01**: "Why use two template parameters?"
   - More flexible design allowing function pointers, functors, and templates
   - Alternative single-parameter design would limit functionality

3. **Ex02**: "Why use a .tpp file?"
   - Templates must be in header files (compiler needs full definition)
   - Separating into .hpp (declaration) and .tpp (definition) improves readability
   - The .tpp is included at the end of .hpp

4. **Ex02**: "What happens with negative index?"
   - Converts to large unsigned int, exceeds size, throws exception
