## Definition

an `automatic default destructor` is added to class if you do not define one. it calls the default destructor of all member objects.

- you can define your own behavior for the object's EOL.
- it is a member function
- it is the name of the class preceded by a `~`
- it has zero arguments and no return type

```cpp
class Cube
{
public:
    int *a, *b;
    Cube() {}
    ~Cube()
    {
        delete a;
        delete b;
        a = nullptr;
        b = nullptr;
    }
};

```

## Usage

You should **never** call a destructor directly. rather, it is automatically called in these situations:

- when the object created in stack goes out of scope
- when the object created in heap is destroyed using `delete` operator

## Important Cases

a custom destructor is essential when an object allocates an external resource that must be closed or freed when the object is destroyed; like:

- heap memory
- open files
- shared memory
