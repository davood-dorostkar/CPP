# const

## 1. Basic `const` Variable
`const` ensures that a variable cannot be modified after initialization.
```cpp
#include <iostream>

int main() {
    const int MAX_AGE = 90;
    // MAX_AGE = 100; // Error: Cannot modify a const variable
    std::cout << "Max Age: " << MAX_AGE << std::endl;
    return 0;
}
```

---

## 2. `const` with Pointers
There are three ways to use `const` with pointers:

### Pointer to `const` Data (Data cannot be changed)
```cpp
const int value = 5;
const int* ptr = &value; // Pointer to constant int
int const* ptr = &value; // the same 
// *ptr = 10; // Error: Cannot modify value
```

### `const` Pointer (Pointer itself cannot change)

what makes the difference with the above method is that here `const` is placed after the `*`.
```cpp
int value = 5;
int value2 = 10;
int* const ptr = &value; // Constant pointer to int
*ptr = 20; // Allowed
// ptr = &value2; // Error: Cannot reassign pointer
```

### `const` Pointer to `const` Data (Neither pointer nor data can change)
```cpp
const int value = 5;
const int* const ptr = &value; 
// *ptr = 10; // Error: Cannot modify value
// ptr = &value2; // Error: Cannot change pointer
```

---

## 3. `const` with Class Methods
A `const` method in a class guarantees that it does not modify the object's state.
```cpp
class Entity {
private:
    int x;
public:
    Entity(int val) : x(val) {}

    int getX() const { // Const method
        return x;
    }

    void setX(int val) { // Non-const method
        x = val;
    }
};
```

---

## 4. `const` with Function Parameters
Passing by `const` reference prevents unnecessary copies and modification.
```cpp
void printEntity(const Entity& e) { // Cannot modify e
    std::cout << "Entity X: " << e.getX() << std::endl;
}
```

---

## 5. `mutable` Keyword
The `mutable` keyword allows a variable to be modified inside a `const` method.
```cpp
class Entity {
private:
    mutable int debugCounter = 0;
public:
    void log() const {
        debugCounter++; // Allowed due to 'mutable'
        std::cout << "Logging Entity" << std::endl;
    }
};
```

---

## Summary
- `const` variables cannot be modified.
- `const` pointers affect either the pointer or the value it points to.
- `const` methods prevent modifying the class.
- `const` references prevent copying and modification.
- `mutable` allows exceptions inside `const` methods.
