Abstraction in C++ is the process of hiding implementation details while showing only the essential features of a class. It is a fundamental concept of object-oriented programming that helps in reducing the complexity of the program by focusing on the essential characteristics of an object.

Abstraction allows creating a simplified model of a complex system, and hiding the implementation details from the user. In C++, abstraction can be achieved through the use of abstract classes and interfaces.

An abstract class is a class that cannot be instantiated, but can be used as a base class for other classes. An abstract class contains at least one pure virtual function, which means that it has no implementation and must be overridden by any derived class that inherits from it.

An interface is a class that only contains pure virtual functions and no data members. Interfaces provide a way to define a contract between a class and the outside world, which specifies the operations that a class must provide without specifying how those operations are implemented.

The main benefits of abstraction are:

1. Simplification: Abstraction simplifies the complexity of a program by providing a high-level view of a system, which focuses on the essential features of an object and hides its implementation details.

2. Modularity: Abstraction allows breaking down a complex system into smaller and more manageable modules, which can be independently developed and maintained.

3. Flexibility: Abstraction provides a way to modify the implementation of a class without affecting its interface, which makes it easier to adapt to changing requirements.

Here is a simple example of abstraction in C++:

```cpp
class Shape {
  public:
    virtual double area() = 0;
    virtual double perimeter() = 0;
};

class Rectangle : public Shape {
  private:
    double width;
    double height;

  public:
    Rectangle(double w, double h) {
      width = w;
      height = h;
    }

    double area() {
      return width * height;
    }

    double perimeter() {
      return 2 * (width + height);
    }
};
```
In this example, the `Shape` class is an abstract class that defines two pure virtual functions `area` and `perimeter`. The `Rectangle` class inherits from the Shape class and provides its own implementation of the virtual functions. The Rectangle class only exposes the essential features of a rectangle (i.e., its area and perimeter), while hiding its implementation details (i.e., the width and height). This is an example of abstraction, where the complexity of the rectangle is hidden behind a simple interface.