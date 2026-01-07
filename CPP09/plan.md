# CPP09 Implementation Plan

## Overview

This module focuses on the **Standard Template Library (STL)**. Each exercise requires using at least one STL container, and once a container is used in an exercise, it cannot be reused in subsequent exercises.

**Container Strategy:**
- **ex00 (Bitcoin Exchange):** `std::map` - ideal for key-value storage with date lookups
- **ex01 (RPN):** `std::stack` - perfect for Reverse Polish Notation evaluation
- **ex02 (PmergeMe):** `std::vector` + `std::deque` - required two different containers

---

## General Requirements (All Exercises)

### Compilation
- Compiler: `c++`
- Flags: `-Wall -Wextra -Werror -std=c++98`

### Makefile Rules
Each exercise must have a Makefile with:
- `$(NAME)` - builds the executable
- `all` - default target
- `clean` - removes object files
- `fclean` - removes objects and executable
- `re` - full rebuild

### Orthodox Canonical Form
All classes must implement:
1. Default constructor
2. Copy constructor
3. Copy assignment operator
4. Destructor

### Code Style (based on CPP01-CPP05)
- Include guards in headers (`#ifndef`, `#define`, `#endif`)
- Private member variables prefixed with `_` (e.g., `_name`)
- `const` correctness on getters and parameters
- Proper exception handling with custom exception classes
- Constructor/destructor messages for debugging (optional)
- No `using namespace` or `friend` keywords

---

## Exercise 00: Bitcoin Exchange

### Objective
Create a program that calculates the value of bitcoin amounts based on historical exchange rates.

### Files to Create
```
ex00/
├── Makefile
├── main.cpp
├── BitcoinExchange.hpp
├── BitcoinExchange.cpp
└── data.csv (provided - bitcoin price database)
```

### Program Specifications
- **Executable name:** `btc`
- **Arguments:** `./btc <input_file>`
- **Input format:** `date | value` (one per line)
- **Date format:** `YYYY-MM-DD`
- **Value range:** float or positive int, 0-1000

### Implementation Steps

#### Step 1: Create the Header File (BitcoinExchange.hpp)
```cpp
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
private:
    std::map<std::string, float> _database;

    // Private helper methods
    bool isValidDate(const std::string& date) const;
    bool isValidValue(const std::string& value, float& result) const;
    float getExchangeRate(const std::string& date) const;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& src);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void loadDatabase(const std::string& filename);
    void processInput(const std::string& filename);
};

#endif
```

#### Step 2: Implement Database Loading (BitcoinExchange.cpp)
1. Open `data.csv` file
2. Parse each line: `date,exchange_rate`
3. Store in `std::map<std::string, float>` with date as key
4. Handle file open errors

#### Step 3: Implement Date Validation
1. Check format `YYYY-MM-DD` using string parsing
2. Validate year (reasonable range)
3. Validate month (1-12)
4. Validate day (1-31, accounting for month)
5. Handle leap years for February

#### Step 4: Implement Value Validation
1. Parse string to float
2. Check range: 0 <= value <= 1000
3. Handle non-numeric input
4. Handle negative numbers ("Error: not a positive number.")
5. Handle overflow ("Error: too large a number.")

#### Step 5: Implement Exchange Rate Lookup
1. Use `std::map::lower_bound()` to find closest date
2. If exact match, use it
3. If no exact match, use previous (lower) date
4. Handle case where date is before all database dates

#### Step 6: Process Input File
1. Open input file
2. Skip header line ("date | value")
3. For each line:
   - Parse date and value
   - Validate date format
   - Validate value
   - Look up exchange rate
   - Calculate and display: `date => value = result`
4. Handle errors with appropriate messages

#### Step 7: Create main.cpp
```cpp
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    try
    {
        BitcoinExchange btc;
        btc.loadDatabase("data.csv");
        btc.processInput(argv[1]);
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

#### Step 8: Create Makefile
```makefile
NAME        = btc
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98
SRCS        = main.cpp BitcoinExchange.cpp
OBJS        = $(SRCS:.cpp=.o)
HEADERS     = BitcoinExchange.hpp

all: $(NAME)

$(NAME): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp $(HEADERS)
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS)

fclean: clean
    rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

### Expected Output Examples
```
$ ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.
```

---

## Exercise 01: Reverse Polish Notation

### Objective
Create an RPN calculator that evaluates mathematical expressions in postfix notation.

### Files to Create
```
ex01/
├── Makefile
├── main.cpp
├── RPN.hpp
└── RPN.cpp
```

### Program Specifications
- **Executable name:** `RPN`
- **Arguments:** `./RPN "expression"`
- **Input numbers:** single digits (0-9)
- **Operators:** `+`, `-`, `*`, `/`
- **No brackets or decimals**
- **Errors go to stderr**

### Implementation Steps

#### Step 1: Create the Header File (RPN.hpp)
```cpp
#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN
{
private:
    std::stack<double> _stack;

    bool isOperator(char c) const;
    bool isDigit(char c) const;
    double performOperation(double a, double b, char op) const;

public:
    RPN();
    RPN(const RPN& src);
    RPN& operator=(const RPN& other);
    ~RPN();

    double evaluate(const std::string& expression);
};

#endif
```

#### Step 2: Implement Token Identification
1. `isOperator()`: check if char is `+`, `-`, `*`, or `/`
2. `isDigit()`: check if char is `0-9`
3. Skip whitespace characters

#### Step 3: Implement Operation Execution
```cpp
double performOperation(double a, double b, char op) const
{
    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0)
                throw std::runtime_error("Division by zero");
            return a / b;
    }
    throw std::runtime_error("Invalid operator");
}
```

#### Step 4: Implement RPN Evaluation Algorithm
```
For each token in expression:
    If token is a number:
        Push onto stack
    Else if token is an operator:
        If stack has fewer than 2 elements:
            Error: insufficient operands
        Pop two operands (b = pop, a = pop)
        Calculate result = a op b
        Push result onto stack
    Else if token is not whitespace:
        Error: invalid token

After processing all tokens:
    If stack has exactly 1 element:
        Return that element as result
    Else:
        Error: invalid expression
```

#### Step 5: Implement Input Validation
1. Check for empty input
2. Check for invalid characters (brackets, letters, etc.)
3. Check for numbers >= 10 (multi-digit)
4. Ensure proper spacing between tokens

#### Step 6: Create main.cpp
```cpp
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    try
    {
        RPN calculator;
        double result = calculator.evaluate(argv[1]);
        std::cout << result << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    return 0;
}
```

#### Step 7: Create Makefile
```makefile
NAME        = RPN
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98
SRCS        = main.cpp RPN.cpp
OBJS        = $(SRCS:.cpp=.o)
HEADERS     = RPN.hpp

all: $(NAME)

$(NAME): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp $(HEADERS)
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS)

fclean: clean
    rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

### Expected Output Examples
```
$ ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$ ./RPN "7 7 * 7 -"
42
$ ./RPN "1 2 * 2 / 2 * 2 4 - +"
0
$ ./RPN "(1 + 1)"
Error
```

---

## Exercise 02: PmergeMe

### Objective
Implement the Ford-Johnson merge-insert sort algorithm using two different containers and compare their performance.

### Files to Create
```
ex02/
├── Makefile
├── main.cpp
├── PmergeMe.hpp
└── PmergeMe.cpp
```

### Program Specifications
- **Executable name:** `PmergeMe`
- **Arguments:** `./PmergeMe <positive integers...>`
- **Algorithm:** Ford-Johnson merge-insert sort
- **Must handle:** at least 3000 integers
- **Containers:** two different ones (vector and deque)
- **Output:** before/after sequences and timing for each container

### Ford-Johnson Algorithm Overview

The merge-insert sort (Ford-Johnson algorithm) minimizes comparisons:

1. **Pair and Compare:** Group elements into pairs, compare each pair
2. **Recursive Sort:** Recursively sort the larger elements of each pair
3. **Binary Insertion:** Insert the smaller elements using binary search in a specific order (Jacobsthal sequence)

### Implementation Steps

#### Step 1: Create the Header File (PmergeMe.hpp)
```cpp
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <utility>

class PmergeMe
{
private:
    std::vector<int> _vec;
    std::deque<int> _deq;

    // Vector implementation
    void mergeInsertSortVector(std::vector<int>& arr);
    void binaryInsertVector(std::vector<int>& arr, int value, int end);

    // Deque implementation
    void mergeInsertSortDeque(std::deque<int>& arr);
    void binaryInsertDeque(std::deque<int>& arr, int value, int end);

    // Jacobsthal sequence helper
    std::vector<int> getJacobsthalSequence(int n);

public:
    PmergeMe();
    PmergeMe(const PmergeMe& src);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void parseInput(int argc, char** argv);
    void sortAndDisplay();
};

#endif
```

#### Step 2: Implement Input Parsing
1. Validate each argument is a positive integer
2. Check for duplicates (optional - subject says discretion)
3. Handle overflow
4. Store in both containers

```cpp
void parseInput(int argc, char** argv)
{
    for (int i = 1; i < argc; ++i)
    {
        // Validate and parse
        std::string arg = argv[i];
        // Check for negative
        if (arg[0] == '-')
            throw std::invalid_argument("Negative number");
        // Parse to long, check overflow
        long num = std::strtol(arg.c_str(), NULL, 10);
        if (num > INT_MAX || num < 0)
            throw std::invalid_argument("Invalid number");
        _vec.push_back(static_cast<int>(num));
        _deq.push_back(static_cast<int>(num));
    }
}
```

#### Step 3: Implement Jacobsthal Sequence Generator
The Jacobsthal sequence determines insertion order: 1, 3, 5, 11, 21, 43, ...
```
J(0) = 0
J(1) = 1
J(n) = J(n-1) + 2*J(n-2)
```

```cpp
std::vector<int> getJacobsthalSequence(int n)
{
    std::vector<int> jacob;
    jacob.push_back(0);
    jacob.push_back(1);
    while (jacob.back() < n)
    {
        int next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }
    return jacob;
}
```

#### Step 4: Implement Ford-Johnson for std::vector

```cpp
void mergeInsertSortVector(std::vector<int>& arr)
{
    if (arr.size() <= 1)
        return;

    // Step 1: Create pairs and identify larger/smaller
    std::vector<std::pair<int, int> > pairs;
    bool hasStraggler = (arr.size() % 2 != 0);
    int straggler = hasStraggler ? arr.back() : 0;

    for (size_t i = 0; i + 1 < arr.size(); i += 2)
    {
        if (arr[i] > arr[i + 1])
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
    }

    // Step 2: Extract larger elements and sort recursively
    std::vector<int> larger;
    for (size_t i = 0; i < pairs.size(); ++i)
        larger.push_back(pairs[i].first);

    mergeInsertSortVector(larger);

    // Step 3: Create main chain with sorted larger elements
    // Build mapping from sorted larger to their smaller partners
    std::vector<int> mainChain = larger;
    std::vector<int> pend;

    // Find smaller element for each larger in sorted order
    for (size_t i = 0; i < larger.size(); ++i)
    {
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].first == larger[i])
            {
                pend.push_back(pairs[j].second);
                pairs[j].first = -1; // Mark as used
                break;
            }
        }
    }

    // Step 4: Insert first smaller element at beginning
    if (!pend.empty())
        mainChain.insert(mainChain.begin(), pend[0]);

    // Step 5: Insert remaining using Jacobsthal sequence order
    std::vector<int> jacob = getJacobsthalSequence(pend.size());
    std::vector<bool> inserted(pend.size(), false);
    inserted[0] = true;

    for (size_t k = 2; k < jacob.size() && jacob[k] <= (int)pend.size(); ++k)
    {
        for (int j = jacob[k]; j > jacob[k - 1]; --j)
        {
            if (j - 1 < (int)pend.size() && !inserted[j - 1])
            {
                binaryInsertVector(mainChain, pend[j - 1], mainChain.size());
                inserted[j - 1] = true;
            }
        }
    }

    // Insert any remaining elements
    for (size_t i = 0; i < pend.size(); ++i)
    {
        if (!inserted[i])
            binaryInsertVector(mainChain, pend[i], mainChain.size());
    }

    // Step 6: Insert straggler if exists
    if (hasStraggler)
        binaryInsertVector(mainChain, straggler, mainChain.size());

    arr = mainChain;
}
```

#### Step 5: Implement Binary Insertion
```cpp
void binaryInsertVector(std::vector<int>& arr, int value, int end)
{
    int left = 0;
    int right = end;

    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    arr.insert(arr.begin() + left, value);
}
```

#### Step 6: Implement Ford-Johnson for std::deque
Similar to vector implementation but using deque operations.

#### Step 7: Implement Timing and Display
```cpp
void sortAndDisplay()
{
    // Display before
    std::cout << "Before:";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << " " << _vec[i];
    std::cout << std::endl;

    // Sort with vector and time
    std::vector<int> vecCopy = _vec;
    clock_t startVec = clock();
    mergeInsertSortVector(vecCopy);
    clock_t endVec = clock();
    double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000;

    // Sort with deque and time
    std::deque<int> deqCopy = _deq;
    clock_t startDeq = clock();
    mergeInsertSortDeque(deqCopy);
    clock_t endDeq = clock();
    double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000;

    // Display after
    std::cout << "After:";
    for (size_t i = 0; i < vecCopy.size(); ++i)
        std::cout << " " << vecCopy[i];
    std::cout << std::endl;

    // Display timing
    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque : " << timeDeq << " us" << std::endl;
}
```

#### Step 8: Create main.cpp
```cpp
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    try
    {
        PmergeMe sorter;
        sorter.parseInput(argc, argv);
        sorter.sortAndDisplay();
    }
    catch (std::exception& e)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    return 0;
}
```

#### Step 9: Create Makefile
```makefile
NAME        = PmergeMe
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98
SRCS        = main.cpp PmergeMe.cpp
OBJS        = $(SRCS:.cpp=.o)
HEADERS     = PmergeMe.hpp

all: $(NAME)

$(NAME): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp $(HEADERS)
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS)

fclean: clean
    rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

### Expected Output Examples
```
$ ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::vector : 0.00031 us
Time to process a range of 5 elements with std::deque : 0.00014 us

$ ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
Before: 141 79 526 321 [...]
After:  79 141 321 526 [...]
Time to process a range of 3000 elements with std::vector : 62.14389 us
Time to process a range of 3000 elements with std::deque : 69.27212 us

$ ./PmergeMe "-1" "2"
Error
```

---

## Testing Checklist

### Exercise 00 (btc)
- [ ] No arguments shows error
- [ ] Invalid file shows error
- [ ] Valid input produces correct calculations
- [ ] Negative values show "Error: not a positive number."
- [ ] Invalid dates show "Error: bad input => ..."
- [ ] Values > 1000 show "Error: too large a number."
- [ ] Dates before database use closest lower date
- [ ] Empty file handling

### Exercise 01 (RPN)
- [ ] Valid expressions calculate correctly
- [ ] Brackets produce error
- [ ] Invalid characters produce error
- [ ] Division by zero handling
- [ ] Empty input produces error
- [ ] Too few operands produces error
- [ ] Multi-digit numbers produce error

### Exercise 02 (PmergeMe)
- [ ] Small sequences sort correctly
- [ ] 3000+ elements handled
- [ ] Negative numbers produce error
- [ ] Non-numeric input produces error
- [ ] Timing displayed for both containers
- [ ] Before/After sequences displayed
- [ ] Algorithm correctness verified

---

## Container Usage Summary

| Exercise | Container(s) Used | Reason |
|----------|------------------|--------|
| ex00 | `std::map` | Key-value pairs, efficient date lookup with `lower_bound` |
| ex01 | `std::stack` | LIFO structure perfect for RPN evaluation |
| ex02 | `std::vector`, `std::deque` | Random access needed for sorting, comparing performance |

**Note:** This allocation ensures no container overlap between exercises as required by the subject.
