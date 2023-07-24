## Circular dependency

when you include two header files in each other and their implementation depend on each other, this results in circular dependency and prevents the code to be compiled correctly. like this:

```cpp
// ClassA.h
#ifndef CLASSA_H
#define CLASSA_H

#include "ClassB.h"

class ClassA {
  ClassB* bPtr;
public:
  void setB(ClassB* b);
};

#endif
```

```cpp
// ClassA.cpp
#include "ClassA.h"

void ClassA::setB(ClassB* b) {
  bPtr = b;
}
```

```cpp
// ClassB.h
#ifndef CLASSB_H
#define CLASSB_H

#include "ClassA.h"

class ClassB {
  ClassA* aPtr;
public:
  void setA(ClassA* a);
};

#endif
```

```cpp
// ClassB.cpp
#include "ClassB.h"

void ClassB::setA(ClassA* a) {
  aPtr = a;
}
```
## The Solution
To avoid this situation you can use a practice called `forward declaration`. the point is that the `include`s are moved to `cpp` files, and also a dummy class is declared in each class. these declarations are meaningless at first, however, it lets the compiler to move forward compiling without being stuck at some point for not knowing about the other class. like this:

```cpp
// ClassA.h
#ifndef CLASSA_H
#define CLASSA_H

class ClassB;  // Forward declaration

class ClassA {
  ClassB* bPtr;
public:
  void setB(ClassB* b);
};

#endif
```

```cpp
// ClassA.cpp
#include "ClassA.h"
#include "ClassB.h"

void ClassA::setB(ClassB* b) {
  bPtr = b;
}
```

```cpp
// ClassB.h
#ifndef CLASSB_H
#define CLASSB_H

class ClassA;  // Forward declaration

class ClassB {
  ClassA* aPtr;
public:
  void setA(ClassA* a);
};

#endif
```

```cpp
// ClassB.cpp
#include "ClassB.h"
#include "ClassA.h"

void ClassB::setA(ClassA* a) {
  aPtr = a;
}
```
