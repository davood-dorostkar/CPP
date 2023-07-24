## Constructor

- Automatic constructor: when you do not define a constructor, the compiler define one for you. the value of members are undefined
- Custom Default constructor: a user-defined constructor with no inputs
- Custom constructor: a user-defined constructor with inputs
  > if any kind of custom constructors are defined, no automatic constructor is defined

## Copy Constructor

You can define a copy constructor in your class. It must take exactly one input, which is a reference to the same object type.

```cpp
class Cube
{
    int _name;
    Cube(const Cube &c) : _name(c.name) {}
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
Cube & Cube::operator=(const Cube & c)
{
    name = c.name;
    return *this;
}
```

The definition and functionality is very similar to copy constructor. Besides syntax, there are two main differences:

1. It returns itself by dereferencing
2. It does not create a new object. instead it is invoked when using a `=` operator
