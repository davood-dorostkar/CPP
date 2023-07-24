### The ability to take many forms

## Function overloading
```cpp
int compute(int a , int b)
{
return abs(a-b);
}

int compute(int a)
{
    return a*a;
}
```
## Operator overloading
The structure:
```cpp
class className {
    ... .. ...
    public:
        returnType operator symbol (arguments) {
            ... .. ...
        } 
    ... .. ...
};
```
Simple example:
```cpp
class Shape 
{
      int length;    
      int width;
      
    public:
      Shape(int l, int w) 
      {
         length = l;
         width = w;
      }
      
      int operator + (Shape shape)
      {
          return (length+shape.length)*(width+shape.width);
      }
		
};

int main(void) 
{
   Shape sh1(4, 4);   
   Shape sh2(2, 6);   
   
   int total = sh1 + sh2;
   return 0;
}
```
A better example:
```cpp
#include<iostream> 
using namespace std; 
  
class Complex {
private: 
    int real, imag; 
public:
    Complex(int r = 0, int i =0)  {real = r;   imag = i;} 
      
    // This is automatically called when '+' is used with 
    // between two Complex objects 
    Complex operator + (Complex const &obj) { 
         Complex res; 
         res.real = real + obj.real; 
         res.imag = imag + obj.imag; 
         return res; 
    } 
    void print() { cout << real << " + i" << imag << endl; } 
}; 
  
int main() 
{ 
    Complex c1(10, 5), c2(2, 4); 
    Complex c3 = c1 + c2; // An example call to "operator+" 
    c3.print(); 
}
```
## Function overriding
the same function from child can override that function from parent
```cpp
#include <iostream>
using namespace std;

class Base {
   public:
    void print() {
        cout << "Base Function" << endl;
    }
};

class Derived : public Base {
   public:
    void print() {
        cout << "Derived Function" << endl;
    }
};

int main() {
    Derived derived1;
    derived1.print();
    return 0;
}
// Output: Derived Function
```
> Exception: using pointers runs the member function in the parent (this is called _static linkage_), example:
```cpp
int main(void) {
   Shape *s;
   Square sq(5,5); 
   Rectangle rec(4,5); 
   
   s = &sq;
   s->get_Area();
   s= &rec;
   s->get_Area();
   return 0;
}
// Output
// This is call to parent class area
// This is call to parent class area
```
## Virtual function
to prevent _static linkage_, you can define the function in parent as virtual
```cpp
class Animal 
{
    protected:
    int age;
    
    public:
    Animal(int a)
    {
        age = a;
    }

    virtual void Eat()
    {
        cout << "Animal eats food" <<endl;
    }

    virtual int get_Age()
    {
        return age;
    }
};
class Dog : public Animal 
{
    public:
    Dog(int a) : Animal(a){}

    void Eat()
    {
        cout << "Dog eats meat" <<endl;
    }
};
```
## Virtual destructor
if you declare the base class destructor as `virtual`, then by deleting the object, both derived and base class destructors are called in the reverse order:
```cpp
#include <iostream>

class Base {
public:
    virtual ~Base() {
        std::cout << "Base destructor called\n";
    }
};

class Derived : public Base {
public:
    ~Derived() override {
        std::cout << "Derived destructor called\n";
    }
};

int main() {
    Base* ptr = new Derived();
    delete ptr;
    return 0;
}
```
```
Derived destructor called
Base destructor called
```