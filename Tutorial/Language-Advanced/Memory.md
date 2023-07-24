## Stack
when you define a variable it is in stack memory. the stack memory is filled from up to down (from large addresses to lower addresses)

after function ends, its stack memory is erased and inaccessible. so do not return local addresses inside a function. this leads to an error:
```cpp
class Cube
{
    int _side;
public:
    Cube(int side)
    {
        _side = side;
    }
};
```
```cpp
Cube* makeCube(int side)
{
    Cube cube(side);
    return &cube; // bad practice. this memory address will be destroyed upon function finish
}
```
## Heap
* the heap memory is totally independent of a functions lifecycle. the only way to store data in heap is by the `new` keyword.

* the heap memory is filled from down to up(from lower addresses to larger addresses- in contrast to stack)

* the only way to free that memory in heap is by keyword `delete`

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

* it always point to 0x0 address (nowhere)
* it is not used by system
* deleting 0x0 is ignored
* accessing 0x0 leads to error

## Arrays in heap
it has a different syntax
```cpp
int* ptr = new int[3];
*ptr = 43;

delete[] ptr;
ptr = nullptr;
```