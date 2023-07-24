Encapsulation in C++ is a mechanism of wrapping data members and member functions (i.e., methods) that operate on them, into a single unit called a class. It is one of the fundamental principles of object-oriented programming (OOP) that allows for data hiding, abstraction, and access control.

In encapsulation, the internal state of an object is hidden from the outside world, and can only be accessed through public methods that are provided by the class. This means that the data can only be modified by the methods of the class, and not directly by other parts of the program.

The main benefits of encapsulation are:

1. Data hiding: Encapsulation allows hiding the implementation details of a class from the outside world, which helps in preventing unauthorized access and modification of data.

2. Abstraction: Encapsulation provides a way to abstract the implementation details of a class and focus on its interface, which simplifies the complexity of the program and makes it easier to use and maintain.

3. Access control: Encapsulation allows controlling the access to the data members of a class through access specifiers (i.e., public, private, and protected), which helps in enforcing security and maintaining the integrity of the data.

Here is a simple example of encapsulation in C++:

```cpp
class BankAccount {
  private:
    double balance;

  public:
    BankAccount(double initialBalance) {
      balance = initialBalance;
    }

    void deposit(double amount) {
      balance += amount;
    }

    void withdraw(double amount) {
      balance -= amount;
    }

    double getBalance() {
      return balance;
    }
};
```
In this example, the `BankAccount` class encapsulates the `balance` data member and the methods that operate on it (i.e., `deposit`, `withdraw`, and `getBalance`). The balance data member is declared as private, which means it can only be accessed from within the class. The public methods of the class provide a way to access and modify the balance data member, while hiding its implementation details. This ensures that the balance can only be modified through the provided methods, and not directly by other parts of the program.