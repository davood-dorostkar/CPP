# Structured Binding

structured bindings is a feature introduced in C++17. Structured bindings allow for a more efficient handling of multiple return values, particularly `tuples` and `pairs`, making the code cleaner and simpler. It simplifies unpacking tuples or pairs.

## Syntax
```cpp
auto[name, age] = std::tuple<std::string, int>("Davood", 30);
```

## Example
```cpp
#include <iostream>
#include <tuple>
#include <string>

std::tuple<std::string, int> CreatePerson()
{
    return {"Davood", 30};
}

int main()
{
    auto[name, age] = CreatePerson(); // structured binding

    std::cout << name << age << std::endl;

    return 0;
}


```

## vs Using structs
this method requires a lot of unnecessary boilerplate code only for getting the return value of the function.
```cpp
#include <iostream>
#include <string>

struct Person
{
    std::string Name;
    int age;
};

Person CreatePerson()
{
    return {"Davood", 30};
}

int main()
{
    Person person = CreatePerson();
    std::string name = person.Name;
    int age = person.age;

    std::cout << name << age << std::endl;

    return 0;
}

```

## vs Using std::get
Instead of using `std::get` with indices to access elements in a tuple, structured bindings allow you to directly unpack the tuple into named variables, making the code more intuitive and easier to understand.

```cpp
#include <iostream>
#include <tuple>
#include <string>

std::tuple<std::string, int> CreatePerson()
{
    return {"Davood", 30};
}

int main()
{
    auto person = CreatePerson();
    std::string name = std::get<0>(person);
    int age = std::get<1>(person);

    std::cout << name << age << std::endl;

    return 0;
}
```

## vs Using std::tie
This method is more readable than the direct use of `std::get<index>(tuple)` for each element, though it still requires multiple lines of code and is not as clean as structured bindings.

```cpp
int main()
{
    std::string name;
    int age;
    std::tie(name, age) = CreatePerson();

    std::cout << name << age << std::endl;

    return 0;
}
```

## Benefits

- **Simplified Code**:
  
  Structured bindings make the code cleaner and more readable by reducing the verbosity and complexity of handling multiple return values from functions.

- **Reduced Boilerplate**:
   - Structured bindings eliminate the need for creating structs solely for the purpose of returning multiple values, thus reducing the amount of boilerplate code and the number of types that clutter the codebase.

- **Enhanced Maintainability**:
   - By using structured bindings, the code is more maintainable as it is easier to follow the logic and understand what each variable represents without navigating through multiple lines of type definitions and `std::get` calls.

- **Versatility**:
   - Structured bindings can handle not just pairs and tuples but also arrays and structs, offering a versatile way to unpack and use data structures directly.