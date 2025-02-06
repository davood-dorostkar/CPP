## What does it mean

There are different type of accessing the memory. You can store a variable directly via `Cube c`, or access it by pointer via `Cube *ptr = &c`, or access it by reference via `Cube &r = c`.

### Pointer

A pointer is an address that points to the allocated location in the memory. the size of a pointer is dependant to the system architecture. (e.g: on a 64-bit system, pointers a 64-bit length)

### Reference

- The reference is actually an alias for an existing variable. so you cannot define a reference to a not-initialized-variable. For this, you must be careful when using references; you must ensure that such a variable exists.
- A reference never stores memory by itself.
- When you change a reference's value you are changing the original value.
- Sometimes refs and ptrs might seem the same; keep in mind that using a ptr, you will have two variables: the original var, and var that stores the address; but with refs, there is only the original var.

![](/images/ptr-ref.PNG)

## Use Cases

We have a triplet: `value`, `pointer`, `reference`. There are 3 cases it is important which one of the triplet to use:

- storage (defining a variable)
- pass by (passing something to a function)
- return by (the return type of a function)

## Using Pointers-Addresses-References

```cpp
int var = 10;
var // the value
&var // the address
```

```cpp
int* ptr = 0x65feb4;
ptr // the address
*ptr // the value
```

```cpp
int var = 10;
int &ref = var; // an alias (reference) to another variable
var = 5; // same result
ref = 5; // same result
```

## Pointer & pointer-to-pointer
if you want a second pointer to point to a first pointer, you need to treat the first pointer like an ordinary variable:
```cpp
int main() {
    int a = 10;          
    int *ptr = &a;       
    int **pptr = &ptr;   // here we get the address of ptr with "&" like a normal variable

    cout << **pptr << endl;  

    return 0;
}
```

![](/images/ptr-to-ptr.jpeg)

## Pass by reference

```cpp
void increment(int &input)
{
    input++; //Note the LACK OF THE addition of '&'
}

int a = 34;
increment(a);
```

Meaning: When the 'increment' function is called with the variable 'a', the function receives a reference to 'a' as the function argument. Any modifications made to the reference 'a' inside the function are actually made to the original variable 'a'.

Therefore, in C++, when you pass a variable by reference to a function, you do not need to dereference the variable inside the function, because the reference parameter already provides direct access to the original variable.

## pass by pointer

### How to use

```cpp
void arrayAsPointer(int *array, int size)
{
    std::cout<<std::setw(5);
    for(int i=0; i<size; i++)
        std::cout<<array[i]<<" ";
    std::cout<<"\n";
}

const int size = 3;
int array[size] = {33,66,99};
arrayAsPointer(array, size);
```

### How it works

When you pass an argument by reference, it does not copy the whole data and it only passes the reference to that memory. However it is important to know that it still makes a copy of that pointer for the lifetime of that function call. consider we have a pointer pointing to an integer:

![](/images/pass-by-pointer1.png)

when we pass it to a function, it makes its own copy which is also pointing to the same location in memory. so here if we dereference the pointer and change its value, the original value will be changed:

![](/images/pass-by-pointer2.png)

but we can still change the pointer itself without concerning about changing the original variable. in this case, we are changing the pointer itself so it means that the copy pointer will point to another location:

![](/images/pass-by-pointer3.png)

```cpp
int passByPointer(int* ptr)
{
    ++ptr;
    return *ptr;
}

int main()
{
    int val = 12;
    int newVal = passByPointer(&val);
    cout << "val: " << val << endl; // returns 12. val is not changed despite that we are changing the argument of the function in it
    cout << "newVal: " << newVal << endl; // returns undefined value (you can also decide to point to an specific location
    return 0;
}
```

## Pass a reference vs pass a pointer

In C++, passing a reference to a function and passing a pointer to a function are both ways to allow the function to modify the value of a variable outside of its own scope. However, there are some differences between the two:

1. Syntax: The syntax for passing a reference and a pointer to a function is different. When passing a reference, you simply use the `&` symbol before the parameter name, like this: `void foo(int& x)`. When passing a pointer, you use the `*` symbol before the parameter name, like this: `void bar(int* x)`.

2. Nullability: Pointers can be null, but references cannot. This means that if you want to allow a function to accept null pointers as input, you must use a pointer parameter. If you use a reference parameter and pass it a null pointer, the program will likely crash.

3. Dereferencing: When using a pointer parameter, you must dereference the pointer to access or modify the value of the variable it points to. With a reference parameter, you can simply use the variable name directly. For example, if you have a pointer to an integer `int* ptr`, you would need to dereference it like this to modify its value: `*ptr = 42`. However, if you have a reference to an integer `int& ref`, you can modify its value directly like this: `ref = 42`.

4. Type safety: When using a pointer parameter, you must be careful to ensure that the pointer points to a valid object of the correct type. With a reference parameter, the type checking is done automatically by the compiler.

### Example

both functions have the same output:

```cpp
void printWithPointer(int *ptr)
{
  std::cout << "\nprintWithPointer:" << std::endl;
  std::cout << *ptr << std::endl; // the value
  std::cout << ptr << std::endl; // the address
}
```

```cpp
void printWithReference(int &ref)
{
  std::cout << "\nprintWithReference:" << std::endl;
  std::cout << ref<< std::endl; // the value
  std::cout << &ref << std::endl; // the address
}
```

```cpp
int main()
{
    int my_integer = 10;
    printWithPointer(&my_integer);
    printWithReference(my_integer);
}
```
## Return by
never return a reference to a stack variable created on the stack of the current function. 

this leads to segfault:

```cpp
int &getValue()
{
    int value = 42;
    return value; // Returning a reference to a stack variable
}

int main()
{
    int &ref = getValue();
    std::cout << ref << std::endl; // Accessing the reference
    return 0;
}
```
