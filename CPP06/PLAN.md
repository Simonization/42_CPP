# CPP06 Implementation Plan - C++ Casts

## Overview
This module focuses on the four C++ cast operators:
- `static_cast` - compile-time type conversions (ex00)
- `reinterpret_cast` - low-level pointer reinterpretation (ex01)
- `dynamic_cast` - runtime polymorphic type identification (ex02)
- `const_cast` - (not used in this module)

---

## Exercise 00: Conversion of Scalar Types

### Directory: `ex00/`

### Files to Create:
- `Makefile`
- `ScalarConverter.hpp`
- `ScalarConverter.cpp`
- `main.cpp`

### Class Design: `ScalarConverter`

**Requirements:**
- Non-instantiable class (private constructor/destructor, delete copy operations)
- Single static method: `static void convert(const std::string& literal)`
- Detect input type, convert to all 4 scalar types, display results

**Cast Type Used: `static_cast`**
- For numeric conversions between char, int, float, double

**Type Detection Logic:**
1. Check for pseudo-literals: `nan`, `nanf`, `+inf`, `-inf`, `+inff`, `-inff`
2. Check for char literal: single character (not digit)
3. Check for int: digits only (with optional leading +/-)
4. Check for float: contains `.` and ends with `f`
5. Check for double: contains `.` without `f` suffix

**Implementation Steps:**

```
1. ScalarConverter.hpp
   - Include guards
   - Private: default constructor, copy constructor, assignment operator, destructor
   - Public: static void convert(const std::string& literal)
   - Private helper methods (optional):
     - static bool isChar(const std::string& str)
     - static bool isInt(const std::string& str)
     - static bool isFloat(const std::string& str)
     - static bool isDouble(const std::string& str)
     - static bool isPseudoLiteral(const std::string& str)

2. ScalarConverter.cpp
   - Implement type detection
   - Parse string to detected type
   - Convert using static_cast to all 4 types
   - Handle special cases:
     - Non-displayable chars (0-31, 127)
     - Overflow for char (< 0 or > 127) and int
     - nan/inf values (impossible for char/int)
   - Output format:
     char: 'c' or "Non displayable" or "impossible"
     int: N or "impossible"
     float: N.Nf (always show decimal)
     double: N.N (always show decimal)

3. main.cpp
   - Test with: 0, nan, 42.0f, 'a', -42, 2147483648, etc.
```

**Output Examples:**
```
./convert 42
char: '*'
int: 42
float: 42.0f
double: 42.0

./convert nan
char: impossible
int: impossible
float: nanf
double: nan
```

---

## Exercise 01: Serialization

### Directory: `ex01/`

### Files to Create:
- `Makefile`
- `Serializer.hpp`
- `Serializer.cpp`
- `Data.hpp`
- `Data.cpp` (optional, can be header-only struct)
- `main.cpp`

### Struct Design: `Data`

**Requirements:**
- Non-empty struct with data members
- Example members: `int id`, `std::string name`, `double value`

### Class Design: `Serializer`

**Requirements:**
- Non-instantiable class
- Two static methods:
  - `static uintptr_t serialize(Data* ptr)`
  - `static Data* deserialize(uintptr_t raw)`

**Cast Type Used: `reinterpret_cast`**
- Converts pointer to integer type and back
- `uintptr_t` is guaranteed to hold any pointer value

**Implementation Steps:**

```
1. Data.hpp
   - Simple struct with data members
   - Example:
     struct Data {
         int         id;
         std::string name;
         double      value;
     };

2. Serializer.hpp
   - Include <cstdint> or <stdint.h> for uintptr_t
   - Include "Data.hpp"
   - Private: constructor, copy, assignment, destructor
   - Public:
     - static uintptr_t serialize(Data* ptr)
     - static Data* deserialize(uintptr_t raw)

3. Serializer.cpp
   - serialize: return reinterpret_cast<uintptr_t>(ptr)
   - deserialize: return reinterpret_cast<Data*>(raw)

4. main.cpp
   - Create Data object
   - Serialize pointer
   - Deserialize back
   - Verify: original pointer == deserialized pointer
   - Verify: data members accessible through both pointers
```

**Test Example:**
```cpp
Data data;
data.id = 42;
data.name = "test";
data.value = 3.14;

uintptr_t raw = Serializer::serialize(&data);
Data* ptr = Serializer::deserialize(raw);

// ptr should equal &data
// ptr->id should equal 42
```

---

## Exercise 02: Identify Real Type

### Directory: `ex02/`

### Files to Create:
- `Makefile`
- `Base.hpp`
- `Base.cpp`
- `A.hpp`
- `B.hpp`
- `C.hpp`
- `main.cpp`

### Class Design

**Base class:**
- Public virtual destructor only
- No Orthodox Canonical Form required

**Derived classes A, B, C:**
- Empty classes
- Publicly inherit from Base
- No Orthodox Canonical Form required

**Cast Type Used: `dynamic_cast`**
- For runtime type identification
- Returns nullptr for pointers if cast fails
- Throws std::bad_cast for references if cast fails

### Functions to Implement:

```cpp
Base* generate(void);
// Randomly creates A, B, or C
// Returns as Base pointer
// Use std::rand() seeded with std::time() or similar

void identify(Base* p);
// Uses dynamic_cast<A*>, dynamic_cast<B*>, dynamic_cast<C*>
// Prints "A", "B", or "C" based on which cast succeeds (non-null)

void identify(Base& p);
// Uses dynamic_cast<A&>, dynamic_cast<B&>, dynamic_cast<C&>
// Must use try-catch since reference cast throws on failure
// Cannot use pointer inside this function
// Prints "A", "B", or "C"
```

**Implementation Steps:**

```
1. Base.hpp / Base.cpp
   - Virtual destructor only
   - Definition in cpp: Base::~Base() {}

2. A.hpp, B.hpp, C.hpp
   - Each: class X : public Base {};
   - Can be header-only (empty class)

3. main.cpp
   - Implement generate(), identify(Base*), identify(Base&)
   - Test multiple times to show random generation
   - Call both identify overloads
   - Clean up memory (delete)
```

**Important Notes:**
- `<typeinfo>` header is FORBIDDEN
- dynamic_cast requires polymorphic base (virtual destructor provides this)
- Reference cast throws std::bad_cast on failure (from <exception>)

**Test Example:**
```cpp
for (int i = 0; i < 5; i++) {
    Base* obj = generate();
    std::cout << "Pointer: ";
    identify(obj);
    std::cout << "Reference: ";
    identify(*obj);
    delete obj;
}
```

---

## File Structure Summary

```
CPP06/
├── ex00/
│   ├── Makefile
│   ├── ScalarConverter.hpp
│   ├── ScalarConverter.cpp
│   └── main.cpp
├── ex01/
│   ├── Makefile
│   ├── Data.hpp
│   ├── Serializer.hpp
│   ├── Serializer.cpp
│   └── main.cpp
└── ex02/
    ├── Makefile
    ├── Base.hpp
    ├── Base.cpp
    ├── A.hpp
    ├── B.hpp
    ├── C.hpp
    └── main.cpp
```

---

## Compilation Requirements

All exercises must:
- Compile with: `c++ -Wall -Wextra -Werror -std=c++98`
- Use Orthodox Canonical Form (ex00, ex01 classes only - ex02 is exempt)
- Include proper header guards
- No `using namespace`
- No STL containers (allowed in module 08+)

---

## Cast Summary for Defense

| Exercise | Cast Used | Purpose |
|----------|-----------|---------|
| ex00 | `static_cast` | Numeric type conversions (char/int/float/double) |
| ex01 | `reinterpret_cast` | Pointer to integer and back |
| ex02 | `dynamic_cast` | Runtime polymorphic type identification |
