## Ternary operator
it is equal to 'if ... then ... else ...' statement
```cpp
A ? B : C;
// equal to
if (A)
{
    B;
}
else
{
    C;
}
```
the only difference is that a ternary expression can be an rvalue, but an if statement cannot:
```cpp
int result = A ? B : C;
```