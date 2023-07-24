## Definition

```cpp
class Cat
{
    int age;

    public:
    void setAge(int age);
    int getAge();
};


void Cat::setAge(int newAge)
{
    age = newAge;
}

int Cat::getAge()
{
    return age;
}
```

### usage:

```cpp
Cat cat;
cat.getAge();
```

- members are private by default
- In member function definitions, you do not need to specify the member scope resolution. it will automatically understand them.
- do not forget `;` after class definition
- do not forget function input part `()` in their declaration
- do not forget function types in their definition
- do not forget scope resolution in function definitions

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
