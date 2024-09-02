# Move Semantics

move semantics were introduced in C++11 and rely on [rvalue references](/Tutorial/Language-Advanced/lvalue-rvalue.md). This feature allows the efficient transfer of resources without unnecessary copying, enhancing performance.

Move semantics become crucial when dealing with objects that require significant resources, such as those involving heap allocations. Traditionally, copying such objects would be resource-intensive, especially in scenarios like passing objects to functions or returning them from functions. With move semantics, instead of copying an object, we move it, thus transferring ownership and avoiding the overhead of copying.

## Categories of Move Semantics

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
## Direct Move & Move with Initialization
Assume:
```cpp
std::unique_ptr<float> data1 = std::make_unique<float>(2.3f);
std::unique_ptr<float> data2 = std::make_unique<float>(55.5f);
```
now consider these two codes <br/>
- Case 1:
```cpp
data2 = std::make_unique<float>(*std::move(data1));
std::cout << *data1.get() << std::endl;
std::cout << *data2.get() << std::endl;
```
- Case 2:
```cpp
data2 = std::move(data1);
std::cout << *data1.get() << std::endl;
std::cout << *data2.get() << std::endl;
```
- In the first code, you are moving the value pointed to by `data1`, not the ownership of the pointer itself. Therefore, `data1` remains valid, but the value it points to becomes `undefined` or garbage.
  
  >Even though this works in this specific case (because float is a simple type), relying on the value after a move is generally dangerous and considered undefined behavior. The move indicates that the value should not be used afterward, as it might be in an invalid state.

- In the second code, you are moving the ownership of the pointer itself from `data1` to `data2`. After this move, `data1` is `null`, and dereferencing it (`*data1.get()`) results in `segfault`, causing an error.

## Example: Moving with Heap Allocation
here the `MyType` data inside `Entity` is heap allocated. So it needs pointer checks. 
```cpp
#include <iostream>
#include <memory>
#include <vector>

class MyType
{
public:
    int a;
    float b;

    MyType() : a(0), b(0)
    {
        std::cout << "default constructor!\n";
    };

    MyType(int in_a, float in_b) : a(in_a), b(in_b)
    {
        std::cout << "base constructor!\n";
    };

    MyType(const MyType& other) : a(other.a), b(other.b)
    {
        std::cout << "copy constructor!\n";
    };

    MyType(MyType&& other) noexcept : a(other.a), b(other.b)
    {
        std::cout << "move constructor!\n";
    };

    MyType& operator=(const MyType& other)
    {
        if (this != &other)
        {
            a = other.a;
            b = other.b;
            std::cout << "copy assignment!\n";
        }
        return *this;
    }

    MyType& operator=(MyType&& other) noexcept
    {
        if (this != &other)
        {
            a = other.a;
            b = other.b;
            std::cout << "move assignment!\n";
        }
        return *this;
    }

    void PrintData() const
    {
        std::cout << "signal: " << a << ", " << b << std::endl;
    }
};

template <typename T>
class Entity
{
private:
    std::unique_ptr<T> _data = nullptr;

public:
    void GetData(std::unique_ptr<T> &data)
    {
        if (_data)
        {
            data = std::make_unique<T>(std::move(*_data));
        }
    }

    void SetData(T& data)
    {
        _data = std::make_unique<T>(std::move(data));
    }

    void PrintData() const
    {
        if (_data)
        {
            std::cout << "_data: " << _data->a << ", " << _data->b << std::endl;
        }
        else
        {
            std::cout << "_data is null\n";
        }
    }
};

void testIntegrity(MyType signal, std::unique_ptr<MyType>& endpointSignal, Entity<MyType>& entity)
{
    entity.PrintData();
    signal.PrintData();

    std::cout << "\nSet Data:\n";
    entity.SetData(signal);
    entity.PrintData();
    signal.PrintData();
    endpointSignal->PrintData();

    signal = {7,8};
    std::cout << "\nGet Data:\n";
    entity.GetData(endpointSignal);
    entity.PrintData();
    signal.PrintData();
    endpointSignal->PrintData();

    std::cout << "\nGet Data:\n";
    entity.GetData(endpointSignal);
    entity.PrintData();
    signal.PrintData();
    endpointSignal->PrintData();

    std::cout << "\nSet Data:\n";
    entity.SetData(signal);
    entity.PrintData();
    signal.PrintData();
    endpointSignal->PrintData();

    std::cout << "\nGet Data:\n";
    entity.GetData(endpointSignal);
    entity.PrintData();
    signal.PrintData();
    endpointSignal->PrintData();
}

int main()
{
    std::unique_ptr<MyType> endpointSignal = std::make_unique<MyType>();
    Entity<MyType> entity;
    MyType signal(2, 3);
    std::cout << "initialized!\n\n";

    testIntegrity(signal, endpointSignal, entity);

    return 0;
}

```
## Example: Moving with Stack Allocation
here the `MyType` data inside `Entity` is stack allocated. So it doesnt  need pointer checks.
```cpp
#include <iostream>
#include <memory>
#include <vector>

class MyType
{
public:
    int a;
    float b;

    MyType() : a(0), b(0)
    {
        std::cout << "default constructor!\n";
    };

    MyType(int in_a, float in_b) : a(in_a), b(in_b)
    {
        std::cout << "base constructor!\n";
    };

    MyType(const MyType& other) : a(other.a), b(other.b)
    {
        std::cout << "copy constructor!\n";
    };

    MyType(MyType&& other) : a(other.a), b(other.b)
    {
        std::cout << "move constructor!\n";
    };

    MyType& operator=(const MyType& other)
    {
        a=other.a;
        b=other.b;
        std::cout << "copy assignment!\n";
        return *this;
    }

    MyType& operator=(MyType&& other)
    {
        a=other.a;
        b=other.b;
        std::cout << "move assignment!\n";
        return *this;
    }

    void PrintData()
    {
        std::cout << "signal: " << this->a << ", " << this->b << std::endl;
    }
};

template <typename T>
class Entity
{
private:
    MyType _data;

public:
    void GetData(std::unique_ptr<T> &data)
    {
        data = std::make_unique<T>(std::move(_data));
    }

    void SetData(MyType& data)
    {
        _data = std::move(data);
    }

    void PrintData()
    {
        std::cout << "_data: " << _data.a << ", " << _data.b << std::endl;
    }

};

void testIntegrity(MyType signal, std::unique_ptr<MyType>& endpointSignal, Entity<MyType> entity)
{
    entity.PrintData();
    signal.PrintData();

    std::cout << "\nSet Data:\n";
    entity.SetData(signal);
    entity.PrintData();
    signal.PrintData();
    endpointSignal->PrintData();

    signal = {7,8};
    std::cout << "\nGet Data:\n";
    entity.GetData(endpointSignal);
    entity.PrintData();
    signal.PrintData();
    endpointSignal->PrintData();

    std::cout << "\nGet Data:\n";
    entity.GetData(endpointSignal);
    entity.PrintData();
    signal.PrintData();
    endpointSignal->PrintData();

    std::cout << "\nSet Data:\n";
    entity.SetData(signal);
    entity.PrintData();
    signal.PrintData();
    endpointSignal->PrintData();

    std::cout << "\nGet Data:\n";
    entity.GetData(endpointSignal);
    entity.PrintData();
    signal.PrintData();
    endpointSignal->PrintData();
}

int main()
{
    std::unique_ptr<MyType> endpointSignal = std::make_unique<MyType>();
    Entity<MyType> entity;
    MyType signal(2, 3);
    std::cout << "initialized!\n\n";

    testIntegrity(signal, endpointSignal, entity);

    return 0;
}

```