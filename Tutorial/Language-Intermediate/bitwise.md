# Bitwise Operations
## Intro
- a two digit hex is at most: 16^0 + 16^1 = 255 ;which also corresponds to 1 byte. 
- an integer takes 4 bytes (typically)

## Bit Shift
### Move to right (divide by 2)
this operation can also be used to divide by 2 very fast.
```c
//          RR|GG|BB|AA
int pixel = 0xFFEECC22; 

// char is 1 byte, so truncates the other 3 bytes
unsigned char r = pixel >> 24; 
unsigned char g = pixel >> 16;
unsigned char b = pixel >> 8;
unsigned char a = pixel >> 0;

printf("r: %d\n", r);
printf("g: %d\n", g);
printf("b: %d\n", b);
printf("a: %d\n", a);
```
### Move to left (multiply by 2)
this operation can also be used to multiply by 2 very fast.
```c
int pixel = 0; 

unsigned char r = 0xFF; 
unsigned char g = 0xEE;
unsigned char b = 0xCC;
unsigned char a = 0x22;

pixel = (r << 24) | (g << 16) | (b << 8) | a;

printf("pixel: %x\n", pixel);
```
## Bit Fields
**Bit fields** in C/C++ are used in `struct` or `union` definitions to allocate a specific number of bits to a field, rather than using the full storage size of a standard data type (e.g., `int`, `char`). This is useful for memory optimization, especially when working with hardware registers, flags, or compact data structures.

### **Syntax**
```c
struct StructName {
    type fieldName : numberOfBits;
};
```

1. **`type`**: The base type (must be an integral type like `int`, `unsigned int`, or `char`).
2. **`fieldName`**: The name of the bit field.
3. **`numberOfBits`**: The number of bits to allocate for the field.


### **Example**
```c
#include <stdio.h>

struct Flags {
    unsigned int is_active : 1; // 1-bit field
    unsigned int is_error : 1;  // 1-bit field
    unsigned int priority : 3;  // 3-bit field
};

int main() {
    struct Flags f;

    f.is_active = 1;
    f.is_error = 0;
    f.priority = 5;

    printf("is_active: %u\n", f.is_active);
    printf("is_error: %u\n", f.is_error);
    printf("priority: %u\n", f.priority);

    return 0;
}
```