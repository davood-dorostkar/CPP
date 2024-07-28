# Move Semantics

move semantics were introduced in C++11 and rely on [rvalue references](/Tutorial/Language-Advanced/lvalue-rvalue.md). This feature allows the efficient transfer of resources without unnecessary copying, enhancing performance.

Move semantics become crucial when dealing with objects that require significant resources, such as those involving heap allocations. Traditionally, copying such objects would be resource-intensive, especially in scenarios like passing objects to functions or returning them from functions. With move semantics, instead of copying an object, we move it, thus transferring ownership and avoiding the overhead of copying.

## Elements of Move Semantics

1. **Move Constructor**
   ```cpp
   ClassName(ClassName&& other);
   ```

2. **Move Assignment Operator**
   ```cpp
   ClassName& operator=(ClassName&& other);
   ```

3. **std::move**
   ```cpp
   ClassName obj1;
   ClassName obj2 = std::move(obj1); // invokes move constructor or move assignment operator
   ```

4. **Rvalue References**
   ```cpp
   void func(ClassName&& obj);
   ```

## Example
```cpp
#include <iostream>
#include <string.h>

class String
{
public:
    String() : m_Size(0), m_Data(nullptr) {}

    String(const char* string)
    {
        std::cout << "Created!\n";
        m_Size = strlen(string);
        m_Data = new char[m_Size];
        memcpy(m_Data, string, m_Size);
    }

    String(const String& other)
    {
        std::cout << "Copied!\n";
        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
    }

    String(String&& other) noexcept
    {
        std::cout << "Moved!\n";
        m_Size = other.m_Size;
        m_Data = other.m_Data;

        other.m_Size = 0;
        other.m_Data = nullptr;
    }

    ~String()
    {
        std::cout << "Destroyed!\n";
        delete m_Data;
    }

    void Print()
    {
        for(uint32_t i = 0; i < m_Size; i++ )
            std::cout << m_Data[i];
        std::cout << "\n";
    }

private:
    uint32_t m_Size;
    char* m_Data;
};
```
```cpp
class Entity
{
public:
    Entity(const String& name)
        : m_Name(name)
    {
    }

    Entity(String&& name)
        : m_Name((String&&)name) // = m_Name(std::move(name))
    {
    }

    void PrintName()
    {
        m_Name.Print();
    }

private:
    String m_Name;
};
```
```cpp
int main() {
    Entity entity("Davood");
    entity.PrintName();
    return 0;
}

```
- In this example there is a basic string class and an entity class that consumes this string. the string class involves copying data, which includes heap allocations, leading to inefficiency. 

- By implementing a `move constructor`, the process is optimized. The move constructor takes an `rvalue reference`, assigns the existing data pointer to the new object.

- here the `m_Name((String&&)name)` part is very important. without casting to an rvalue, the object will still be copied, not moved. you need to explicitly specify it as an rvalue. this is also equivalent to `m_Name(std::move(name))`. however `std::move` is preferred and more flexible.

- the output of this code is: 
    ```
    Created!
    Moved!
    Destroyed!
    Davood
    Destroyed!
    ```
    this means that an rvalue String is created, then it moved to an Entity; then the rvalue **temporary** object is deleted. then at the end of the program, the Entity is deleted.

## std::move
- `std::move` is a function provided by the C++ standard library to indicate that an object can be moved.
- It essentially casts an object to an `R-value reference`, allowing the `move constructor` or `move assignment operator` to be called. it does not actually move anything, but rather indicates that a move is allowed.

### Example
take the above example, with this:
```cpp
int main() {
    String string = "Hello";
    String dest = std::move(string);
    return 0;
}
```
this syntax is also correct:
```cpp
String dest(std::move(string));
```

## Move Assignment Operator
- This operator is used to move an object into an `existing object`, unlike the `move constructor` which creates a new object.
- It involves transferring ownership of resources from one object to another.
- Key steps:
  - Ensure `self-assignment safety` by checking if the source and destination are the same object. without checking you might end up deleting everything.
  - Delete the current object's resources to `avoid memory leaks`.
  - Move the data and reset the source object's state.

### Example
```cpp
// add this definition to the above example:
String& operator=(String&& other) noexcept
{
    if(this != &other)
    {
        std::cout << "Moved!\n";

        delete [] m_Data;

        m_Size = other.m_Size;
        m_Data = other.m_Data;

        other.m_Size = 0;
        other.m_Data = nullptr;
    }
    return *this;
}
```
then try it:
```cpp
int main() {
    String apple = "Apple";
    String dest;

    std::cout << "Apple: ";
    apple.Print();
    std::cout << "Dest: ";
    dest.Print();

    dest = std::move(apple);

    std::cout << "Apple: ";
    apple.Print();
    std::cout << "Dest: ";
    dest.Print();
    return 0;
}
```
the ouput:
```
Created!
Apple: Apple
Dest: 
Moved!
Apple: 
Dest: Apple
Destroyed!
Destroyed!
```
### vs Move Constructor
the Move constructor actually creates a `new` object based on the other object, but move assignment operator sets the `existing` object to the other one.

```cpp
String(String&& other) // Move constructor
String& operator=(String&& other) //move assignment operator
```

### vs Copy Assignment Operator
the [Copy Assignment Operator](/Tutorial/Language-Advanced/Constructors.md#copy-assignment-operator) `copies` an `lvalue` object to existing desination, but move assignment operator `sets` an `rvalue` object to existing destination, and deletes the other one.

```cpp
String& operator=(const String& other) // copy assignment operator
String& operator=(String&& other) //move assignment operator
```
