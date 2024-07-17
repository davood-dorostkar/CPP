## Scopes
we have four different types of scopes:
- class scope
  ```cpp
  class Entity
  {

  }
  ```
- function scope
  ```cpp
  int main()
  {

  }
  ```
- if statements/loops scopes
  ```cpp
  if(true)
  {

  }
  ```
- empty scopes
  ```cpp
  {

  }
  ```

## Stack (Scoped Variables)

- variables declared within a scope on the stack are automatically destroyed when the scope ends, unlike heap-allocated variables which persist until explicitly deleted

- the stack memory is filled from up to down (from large addresses to lower addresses)

- after function ends, its stack memory is erased and inaccessible. so do not return local addresses inside a function. this leads to an error:

```cpp
Cube* makeCube(int side)
{
    Cube cube(side);
    return &cube; // bad practice. this memory address will be destroyed upon function finish
}
```
to deal with this issue we can do two things:
1. create it in the heap
```cpp
Cube* CreateCube()
{
    Cube* cube = new Cube();
    return cube;
}
```
2. preallocate memory
```cpp
void CreateCube(Cube* cube)
{
    // fill the input cube
}

int main()
{
    Cube c;
    CreateCube(c);
}
```

## Heap

- the heap memory is totally independent of a functions lifecycle. the only way to store data in heap is by the `new` keyword.

- the heap memory is filled from down to up(from lower addresses to larger addresses- in contrast to stack)

- the only way to free that memory in heap is by keyword `delete`

### Making Scoped Heap Variables
It is possible to restrict the lifetime of a heap allocatd variable to scopes like stack variables. it is somehow similar to `unique_ptr` as it is also scoped.
```cpp
class Entity
{
public:
    Entity()
    {
        std::cout << "Created!\n";
    }

    ~Entity()
    {
        std::cout << "Destroyed!\n";
    }

};

class ScopedPtr
{
private:
    Entity* m_Ptr;
public:
    ScopedPtr(Entity* ptr)
        : m_Ptr(ptr)
    {
    }

    ~ScopedPtr()
    {
        delete m_Ptr;
    }
};

int main()
{
    { // scoped heap allocated variable
        ScopedPtr e = new Entity(); // implicit conversion
    }
    std::cin.get();
    return 0;
}

```

## new

it always does 3 tasks:

1. allocate memory to the heap
2. initialize that data structure
3. return a pointer to the start of the data structure

it is interesting that in the code below, the variable `intPrt` is stored in `stack`, while the right hand side is stored in `heap`. in fact, the `intPrt` is a pointer in stack that is pointing to an `int` memory inside heap.

```cpp
int *intPrt = new int;
```

## new class

If you use this method to instantiate classes, Because `c` is actually a pointer and not a real class, you should first dereference it in order to access its members:

```cpp
Cube *c = new Cube;

(*c).getLength();
```

This syntax is weird; so in C++ we have the arrow operator `->` which does the same thing and is better syntax:

```cpp
Cube *c = new Cube;

c->getLength();
```

## nullptr

although the `delete` operator frees memory from heap, the pointer is still not removed, and trying to access its pointing address (which no longer exist) is dangerous. a good practice is to set that pointer to `nulptr` after delete:

```cpp
int* ptr = new int;
*ptr = 43;

delete ptr;
ptr = nullptr;
```

nullptr has these features:

- it always point to 0x0 address (nowhere)
- it is not used by system
- deleting 0x0 is ignored
- accessing 0x0 leads to error

## Arrays in heap

it has a different syntax

```cpp
int* ptr = new int[3];
*ptr = 43;

delete[] ptr;
ptr = nullptr;
```

## Segfault

accessing an null pointer will lead to a segmentation fault:

```cpp
int* n = nullptr;
std::cout << *n << std::endl;
```

but accessing an uninitialized pointer will lead to undefined bahavoior.

```cpp
int* x;
```

At least a segfault is predictable! ways to ensure this:

### In the stack

```cpp
// Explicitly initializing a pointer to nullptr
int* y = nullptr;
```

```cpp
// Other ways to initialize
int* y2(nullptr);
int* y3{nullptr}; // C++11
```

Use defautl constructor to safely initialize custom classes:

```cpp
// b will be default initialized
Box b;
```

### In the heap

```cpp
int* r = new int(0);
```
