## Constructor

- Automatic constructor: when you do not define a constructor, the compiler define one for you. the value of members are undefined
- Custom Default constructor: a user-defined constructor with no inputs
- Custom constructor: a user-defined constructor with inputs
  > if any kind of custom constructors are defined, no automatic constructor is defined

## Initializer List
In C++, when you create an object, you can pass arguments to its constructor using an initializer list. 

> It is important that you initialize the members in the same order that they are defined in the class, otherwise you may get dependency errors. this is different in different compilers, but avoid the risk.

- **Performance Improvement**:
  - Avoids double initialization: Reduces the overhead of constructing and then re-assigning member variables.

- **Code Clarity**:
  - Cleaner constructors: Keeps the constructor body free from clutter, making it easier to understand the main logic of the constructor.

- **Mandatory Initialization**:
  - Required for certain types: Some types (like references and const members) must be initialized using initializer lists because they cannot be assigned values later.

- **Consistent Initialization**:
  - Ensures correct order: Members are always initialized in the order they are declared in the class, which can prevent subtle bugs related to initialization order.

- **Code Style and Readability**:
  - Improved readability: Keeps initialization separate from other constructor logic, making the code more readable and maintainable.
  - Preferred by convention: Adhering to common C++ coding conventions and best practices.

### Example
```cpp
#include <iostream>
#include <string>

class MyClassWithMember {
private:
    int memberVariable1;
    int memberVariable2;

public:
    MyClassWithMember(int value1, int value2)
        : memberVariable1(value1),
        : memberVariable2(value2)
    {
        // Constructor body (if needed)
    }
};


MyClassWithMember obj1(42, 3); // Instantiation
```
## Initilizer List with Parent Class
In C++, when you have a class that inherits from another class, you can use the constructor initializer list to specify how the base class constructor should be called. This allows you to provide any necessary arguments to the base class constructor.
```cpp
class MyBaseClass {
private:
    std::string baseMessage;
public:
    MyBaseClass(const std::string& message)
        : baseMessage(message)
    {
        // Constructor body (if needed)
    }
};

class MyDerivedClass : public MyBaseClass {
private:
    int derivedValue;
public:
    MyDerivedClass(const std::string& message, int value)
        : MyBaseClass(message),  // Initialize MyBaseClass using an initializer list
          derivedValue(value)     // Initialize derivedValue using an initializer list
    {
        // Constructor body (if needed)
    }
};


MyDerivedClass obj2("Hello from Base", 10); // Instantiation
```

### Important: How Initializer list works
**in short: it calls the member constructor internally**

assume we have
```cpp
class MyClass
{
public:
    MyClass(int size)
        : area(size, std::vector<double>(size, 0.0)) {}
private:
    std::vector<std::vector<double>> area;
};
```
this means:

- Initialize the area member variable using the constructor of `std::vector<std::vector<double>>` that takes two arguments:

  - An integer size (number of outer vectors)

  - A vector of doubles (each inner vector)
 
for example if we have this:
```cpp
class MyClass
{
public:
    MyClass(int a)
        : x(a) {}
private:
    int x;
};
```
it doesn't mean `x = a;`, instead it means `x = int(a);` which is calling the `int` constructor. this understanding becomes more important for complex types.

## Copy Constructor

You can define a copy constructor in your class. It must take exactly one input, which is a reference to the same object type.

```cpp
class Cube
{
    int name;
    Cube(const Cube &c) : name(c.name) {}
};
```

In three cases, the copy constructor will be invoked automatically:

- When passing an object to a function (when the functions gets something as input, actually a copy of that is generated-except in references)
- When a function returns an object (that object is copied from the function stack to the main stack)
- When assinging an object to a variable (the object is copied into variable)

```cpp
#include <iostream>

class Cube
{
public:
    int name;
    Cube() {}
    Cube(const Cube &c) : name(c.name) {}
};

Cube func(Cube c)
{
    std::cout << c.name << std::endl;
    return c;
}

int main()
{
    Cube c;
    Cube cc = func(c);
}
```

> Note: in the below situation, no copy constructor will be invoked. Because that is just an assignment and nothing is being created at all.

```cpp
int main()
{
    Cube c;
    Cube cc;
    cc = c;
}
```

## Copy Assignment Operator

Definition:

```cpp
Cube& Cube::operator=(const Cube& c)
{
    name = c.name;
    return *this;
}
```

The definition and functionality is very similar to copy constructor. Besides syntax, there are two main differences:

1. It returns itself by dereferencing
2. It does not create a new object. instead it is invoked when using a `=` operator
