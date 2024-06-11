# std::find_if

The `std::find_if` algorithm is part of the C++ Standard Library and is used to find the first element in a range that satisfies a given predicate. It is defined in the `<algorithm>` header.

```cpp
iterator find_if(iterator first, iterator last, UnaryPredicate pred);
```

- **`first`**: An iterator to the beginning of the range.
- **`last`**: An iterator to the end of the range.
- **`pred`**: A unary predicate function (or function object) that returns `true` for the element it is searching for.

## How the Predicate Works

- The predicate function is applied to each element in the range `[first, last)`.
- The predicate must take a single argument of the same type as the elements in the range.
- The predicate must return a boolean value (`true` or `false`).

## Practical Example

Consider the following example with a list of integers to find the first even number:

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

bool isEven(int n) {
    return n % 2 == 0;
}

int main() {
    std::vector<int> numbers = {1, 3, 5, 6, 7, 8};

    auto it = std::find_if(numbers.begin(), numbers.end(), isEven);

    if (it != numbers.end()) {
        std::cout << "First even number: " << *it << std::endl;
    } else {
        std::cout << "No even number found." << std::endl;
    }

    return 0;
}
```

1. **Range**:
   - `numbers.begin()` to `numbers.end()`

2. **Predicate**:
   - `isEven` function: `bool isEven(int n) { return n % 2 == 0; }`