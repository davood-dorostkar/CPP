# Tuple

In C++, you can use `std::tuple` to store  any N-tuple of values. `std::tuple` is a generalization of `std::pair` and allows you to store multiple values of different types in a single object.

## General usage

```cpp
#include <tuple>
std::tuple<int, double, std::string> triple = std::make_tuple(42, 3.14, "hello");

    // Accessing elements
    int firstElement = std::get<0>(triple);
    double secondElement = std::get<1>(triple);
    std::string thirdElement = std::get<2>(triple);
```

## Specializing tuple

If you're working with triples frequently and want to make your code more readable, you might also consider creating a simple `struct` to represent the triple:

```cpp
struct Triple {
    int first;
    double second;
    std::string third;
};


// Creating a Triple
Triple triple = {42, 3.14, "hello"};

// Accessing elements
int firstElement = triple.first;
double secondElement = triple.second;
std::string thirdElement = triple.third;
```

## Eigen for 3D

If you're working with 3D geometry and performance is critical, you might consider using a specialized library that is designed for efficient 3D vector and point operations.

```cpp
#include <Eigen/Dense>

// Using Eigen for 3D point
Eigen::Vector3d point(1.0, 2.0, 3.0);

// Accessing elements
double x = point.x();
double y = point.y();
double z = point.z();
```