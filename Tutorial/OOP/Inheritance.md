## Define child class
```cpp
class Rectangle: public Shape {
   public:
      // definitions
};
```
## Same Constructor
```cpp
Rectangle() : Shape() {} 
```
## Access control
it can be `public`, `private`, or `protected`. 

`private` access means that all members of the base class are treated as private to the child class. similar for `protected`. 

if the access control is private, the members of base class are not available anymore and you should refer the members of the base class explicitly, like:
```cpp
void ChildClass::foo(int in)
{
    BaseClass::baseFunction(in); 
}
```
## Types of inheritance
### Single inheritance
inheritance of one class to another class (also known as simple, basic inheritance)

![](/images/single-inheritance.jpg)
```cpp
class Animal {
  public:
    void eat() {
        cout << "Eating..." << endl;
    }
};

class Dog : public Animal {
  public:
    void bark() {
        cout << "Barking..." << endl;
    }
};

int main() {
  Dog dog;
  dog.eat(); // prints "Eating..."
  dog.bark(); // prints "Barking..."
}

```
### Multiple inheritance
when there is more than one base class

the child has access to all its parents' members

![](/images/multiple-inheritance.jpg)
```cpp
class Mammal {
  public:
    void feedMilk() {
        cout << "Feeding milk..." << endl;
    }
};

class Bird {
  public:
    void layEggs() {
        cout << "Laying eggs..." << endl;
    }
};

class Platypus : public Mammal, public Bird {
  public:
    void swim() {
        cout << "Swimming..." << endl;
    }
};

int main() {
  Platypus platypus;
  platypus.feedMilk(); // prints "Feeding milk..."
  platypus.layEggs(); // prints "Laying eggs..."
  platypus.swim(); // prints "Swimming..."
}

```
### Multilevel inheritance
one class is derivied from a class that is also a derived class

![](/images/multilevel-inheritance.jpg)
```cpp
class Animal {
  public:
    void eat() {
        cout << "Eating..." << endl;
    }
};

class Dog : public Animal {
  public:
    void bark() {
        cout << "Barking..." << endl;
    }
};

class Labrador : public Dog {
  public:
    void playFetch() {
        cout << "Playing fetch..." << endl;
    }
};

int main() {
  Labrador labrador;
  labrador.eat(); // prints "Eating..."
  labrador.bark(); // prints "Barking..."
  labrador.playFetch(); // prints "Playing fetch..."
}

```
### Hierarchical inheritance
there is more than one derivied class from a base class

![](/images/hierarchical-inheritance.jpg)
```cpp
class Animal {
  public:
    void eat() {
        cout << "Eating..." << endl;
    }
};

class Dog : public Animal {
  public:
    void bark() {
        cout << "Barking..." << endl;
    }
};

class Cat : public Animal {
  public:
    void meow() {
        cout << "Meowing..." << endl;
    }
};

int main() {
  Dog dog;
  Cat cat;
  dog.eat(); // prints "Eating..."
  dog.bark(); // prints "Barking..."
  cat.eat(); // prints "Eating..."
  cat.meow(); // prints "Meowing..."
}

```
### Hybrid inheritance
mixing more than one type of inheritance

![](/images/hybrid-inheritance.jpg)
```cpp
class Shape {
  public:
    virtual void draw() = 0;
};

class Circle : public Shape {
  public:
    void draw() {
        cout << "Drawing a circle" << endl;
    }
};

class Square : public Shape {
  public:
    void draw() {
        cout << "Drawing a square" << endl;
    }
};

class ColoredShape : public Shape {
  public:
    virtual void setColor(string color) = 0;
};

class ColoredCircle : public Circle, public ColoredShape {
  public:
    void setColor(string color) {
        cout << "Setting circle color to " << color << endl;
    }
};

int main() {
  ColoredCircle cc;
  cc.draw(); // prints "Drawing a circle"
  cc.setColor("red"); // prints "Setting circle color to red"
}
```