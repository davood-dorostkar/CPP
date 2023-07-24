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