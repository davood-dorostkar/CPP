## Types sizes
```
Int ("%d"): 32 Bit integer
Long ("%ld"): 64 bit integer
Char ("%c"): Character type
Boolean (either true or false)
Float ("%f"): 32 bit real value
Double ("%lf"): 64 bit real value
```
## Type Conversion
### Implicit conversion -> automatically by compiler
```cpp
int a = 1;
float b = 1.1;
a = b;
```
### Explicit conversion -> manually
* C-style cast:
```cpp
b = (int)a;
```
* Cast operators:
1. static_cast
2. const_cast
3. reinterpret_cast
4. dynamic_cast
## Enum
simple example:
```cpp
 enum MONTH {Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};
```
which means:
```cpp
 Jan = 0
 Feb = 1
 etc.
```
The Enum naming convention in Microsoft is singular; but I prefer plural to avoid situations like this:
```cpp
    public class Person
    {
        public enum Gender
        {
            Male,
            Female
        }
        //Won't compile: auto-property has same name as enum
        public Gender Gender { get; set; }  
    }
```
### Implicit conversion
convert char and int to float is ok:
```cpp
int a = 10;
float b = a;
```
convert float to char is not valid

convert float to int truncates the data:
```cpp
float a = 10.1;
int b = a;
// b = 10
```