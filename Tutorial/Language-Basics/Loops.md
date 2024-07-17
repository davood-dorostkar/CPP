## For loop sequence

![](/images/for-loop.jpeg)

## Switch-case

- It only accepts `int`, `char`, `short`, `long` types
- `break` is optional, but if you do not use, the next cases will also be executed
- `default` is optional

```cpp
char operation;
std::cin >> operation;

switch (operation)
{
    case '+': std::cout << in1+in2 << std::endl; break;
    case '-': std::cout << in1-in2 << std::endl; break;
    case '*': std::cout << in1*in2 << std::endl; break;
    case '/': std::cout << in1/in2 << std::endl; break;
    default:std::cout << "not a valid operation"<< std::endl;
}
```

## Modern For loops

in the simple form, the actual values are not affected.

```cpp
int list[3] = {1, 2, 3};
for(int i : list) // here i is just a copy
{
    i=100;
}
```

if you want to change the list values:

```cpp
int list[3] = {1, 2, 3};
for(int &i : list) // here i is the original value
{
    i=100;
}
```

if you do not want to change original values, but want to avoid copying:

```cpp
int list[3] = {1, 2, 3};
for(const int &i : list) // here i is the original value and not changeable
{
    i=100;
}
```
