# Smart Pointers
smart pointers are wrappers around raw pointers, except they handle memory allocation automatically. they remove the need to `delete` pointers manually.

## std::unique_ptr
- it is a scoped pointer. meaning it will be automatically removed if it goes out of scope.
  
  we can easily define a scoped pointer like this (also checkout [Memory management](/Tutorial/Language-Advanced/Memory.md)):
  ```cpp
    template<typename T>
    class scoped_ptr
    {
    private:
        T* m_Ptr;
    public:
        scoped_ptr(T* ptr)
            : m_Ptr(ptr)
        {
        }

        ~scoped_ptr()
        {
            delete m_Ptr;
        }
    };

    int main()
    {
        {
            scoped_ptr<int> e = new int(0);
        }
        std::cin.get();
        return 0;
    }
    ``` 
- it cannot be copied. so no more than 1 object can point to the same memory location. because when the first object is removed, the second object will remain dangling.
- you can only move the ownership to another object.
- `std::make_unique` is the analogy for `new`
- two ways of defining (the second is preferred):
```cpp
std::unique_ptr<int> ptr(new int());
std::unique_ptr<int> ptr = make_unique<int>();
```
- `reset`:

    - **Release the current object**: If called with no arguments, reset releases the ownership of the current object and deletes it.
    - **Take ownership of a new object**: If called with a raw pointer argument, reset deletes the current object (if any) and takes ownership of the new object.
   ```cpp
    std::unique_ptr<int> uptr = std::make_unique<int>(10);
    uptr.reset();  // Releases and deletes the currently managed object.
    uptr.reset(new int(20));  // Now uptr manages a new integer with value 20.
   ```
### make unique ptr from shared ptr
you cannot make a unique ptr directly from a shared pointer. you will get compiler error. however, you can make from it, but they will be disconnected:
```cpp
std::shared_ptr<int> sptr = std::make_shared<int>(10);
std::unique_ptr<int> uptr = nullptr;

uptr = std::make_unique<int>(*std::move(sptr));
std::cout << "Moved shared ptr to unique ptr!"<< std::endl;
std::cout << "shared ptr: " << *sptr << std::endl;
std::cout << "unique ptr: " << *uptr << std::endl;

*sptr = 20;
std::cout << "\nUpdated shared ptr!"<< std::endl;
std::cout << "shared ptr: " << *sptr << std::endl;
std::cout << "unique ptr: " << *uptr << std::endl;

*uptr = 30;
std::cout << "\nUpdated unique ptr!"<< std::endl;
std::cout << "shared ptr: " << *sptr << std::endl;
std::cout << "unique ptr: " << *uptr << std::endl;
```
the above code is the same as this:
```cpp
uptr = std::make_unique<int>(*sptr);
```
### Example
```cpp
#include <iostream>
#include <memory>  

class MyClass {
public:
    MyClass() { std::cout << "MyClass Constructor\n"; }
    ~MyClass() { std::cout << "MyClass Destructor\n"; }
    void display() { std::cout << "MyClass Display\n"; }
};

int main() {
    std::unique_ptr<MyClass> ptr1(new MyClass());
    ptr1->display();

    // Transfer ownership to ptr2
    std::unique_ptr<MyClass> ptr2 = std::move(ptr1);

    // ptr1 is now empty, and ptr2 owns the MyClass instance
    if (ptr1 == nullptr) {
        std::cout << "ptr1 is empty\n";
    }

    ptr2->display();

    // No need to delete manually; it will be deleted when ptr2 goes out of scope
    return 0;
}

```
## std::shared_ptr
- more than 1 shared pointers can point to the same memory location. there is a `reference count` for the shared pointer that stores the list of all of them. 
- the memory is only freed when the reference count is empty. otherwise it will remain.
- it can be copied.
- `std::make_shared` is the analogy for `new`
- two ways of defining (the second is preferred):
    ```cpp
    std::shared_ptr<int> ptr(new int());
    std::shared_ptr<int> ptr = make_shared<int>();
    ```
- Converting a `unique_ptr` to a `shared_ptr` is a common need when you start with exclusive ownership and then want to allow shared ownership. The correct way is by using `std::move`. This transfers ownership from the `unique_ptr` to the `shared_ptr`. After this operation, the unique_ptr will no longer own the resource (it becomes empty).
- `reset`:

    - **Release the current object**: If called with no arguments, reset decrements the reference count of the currently managed object and releases it if this was the last reference.
    - **Take ownership of a new object**: If called with a raw pointer argument, reset decrements the reference count of the current object (if any), deletes it if there are no other references, and takes ownership of the new object.
   ```cpp
    std::shared_ptr<int> sptr = std::make_shared<int>(10);
    sptr.reset();  // Releases the current object if this was the last reference.
    sptr.reset(new int(20));  // Now sptr manages a new integer with value 20.
    ```
- **Dealing with Deferred Rendering**:
   - game engines use deferred rendering, meaning rendering commands are collected and executed later. This requires assets to remain in memory until rendering is complete. Shared pointers ensure these assets are not deleted prematurely, which would lead to crashes or rendering errors. Shared pointers ensure that all objects required by these commands are kept alive until the commands are executed.

- **Multi-Threading**:
   - Shared pointers are thread-safe, allowing multiple threads to share ownership of an object without race conditions. This is crucial for ensuring consistency and correctness in a multi-threaded environment. (the ref increment/decrement is done atomically)

- **Performance Considerations**
  - shared pointers come with some overhead due to atomic operations for thread safety. However, they argue that this overhead is negligible compared to the benefits of simplified and safer memory management.
  - In performance-critical sections, raw pointers or unique pointers might be used, but for general asset management, shared pointers provide a good balance of safety and convenience.

### Example
```cpp
#include <memory>
#include <iostream>

int main() {
    // Create a unique_ptr
    std::unique_ptr<int> uptr = std::make_unique<int>(10);
    
    // Convert unique_ptr to shared_ptr
    std::shared_ptr<int> sptr = std::move(uptr);
    
    // Now sptr owns the resource, uptr is empty
    if (!uptr) {
        std::cout << "uptr is now empty" << std::endl;
    }
    
    std::cout << "sptr owns the resource: " << *sptr << std::endl;
    
    return 0;
}
```
## std::weak_ptr
- just like the shared pointer, but it is not included in the reference count. so the last shared pointer will free the memory even if there is still a weak pointer left.
- you can define it with assigning to a shared pointer.
- Weak pointers allow access to an object without owning it, avoiding the problem of preventing the object from being deleted when it is no longer needed.
- there are great features for weak pointer, including converting a weak pointer to a shared pointer using the `lock` method, checking if the object is still valid with `expired`, and understanding reference counts with `use_count`.
- Both `wp.lock()` and `wp.expired()` are correct methods to check the validity of a std::weak_ptr. `wp.lock()` is typically preferred when you need to use the object, as it provides a std::shared_ptr that can be used directly. `wp.expired()` is useful when you only need to check the validity without accessing the object.
```cpp
if (auto sp = wp.lock()) {
    // wp is valid
} else {
    // wp is expired
}

if (!wp.expired()) {
    // wp is valid
} else {
    // wp is expired
}

```  
- **Advantages over Raw Pointers**: Weak pointers prevent crashes and undefined behavior caused by accessing freed memory, which is a risk with raw pointers.
- **Cyclical Dependency Management**: Weak pointers are crucial in scenarios where objects reference each other, preventing memory leaks caused by circular references.
‍‍‍
```cpp
#include <iostream>
#include <memory>

struct B; // forward declaration

struct A {
    std::shared_ptr<B> b_ptr;
    ~A() { std::cout << "A destroyed" << std::endl; }
};

struct B {
    std::weak_ptr<A> a_ptr; // use weak_ptr to break the cycle
    ~B() { std::cout << "B destroyed" << std::endl; }
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->b_ptr = b;
    b->a_ptr = a;

    // if both a and b were shared pointers, none of them would be destroyed
    return 0;
}

```
### Example
```cpp
#include <iostream>
#include <memory>

struct Object
{
    ~Object() { std::cout << "Deleted object\n"; }
};

struct Manager
{
    std::weak_ptr<Object> Obj;

    void Func()
    {
        if (auto obj = Obj.lock()) // here obj will be an std::shared_ptr<Object>; lock helps in multithreading situations
        {
            std::cout << "object exists so locked\n";
        }

        if (Obj.expired())
        {
            std::cout << "object is already expired\n";
        }
        std::cout << Obj.use_count() << std::endl;
    }
};

Manager manager;

int main()
{
    {
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    manager.Obj = obj;
    manager.Func();
    }
    manager.Func();
}      
```
## Smart Pointers Example
```cpp
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

class Resource {
public:
    Resource(const std::string& id) : id_(id) {
        std::cout << "Resource " << id_ << " created." << std::endl;
    }

    ~Resource() {
        std::cout << "Resource " << id_ << " destroyed." << std::endl;
    }

    void use() {
        std::cout << "Using resource " << id_ << std::endl;
    }

private:
    std::string id_;
};

class ResourceManager {
public:
    ~ResourceManager() {
        std::cout << "ResourceManager destroyed. Releasing resources." << std::endl;
    }

    void addUniqueResource(const std::string& id) {
        uniqueResources_[id] = std::make_unique<Resource>(id);
    }

    void addSharedResource(const std::string& id) {
        std::shared_ptr<Resource> ptr = std::make_shared<Resource>(id);
        sharedResources_[id] = ptr;
    }

    void useResource(const std::string& id) {
        auto uit = uniqueResources_.find(id);
        if (uit != uniqueResources_.end()) {
            uit->second->use();
        } else {
            auto sit = sharedResources_.find(id);
            if (sit != sharedResources_.end()) {
                sit->second->use();
            } else {
                std::cout << "Resource " << id << " not found." << std::endl;
            }
        }
    }

    std::shared_ptr<Resource> getSharedResource(const std::string& id) {
        auto sit = sharedResources_.find(id);
        if (sit != sharedResources_.end()) {
            return sit->second;
        } else {
            std::cout << "Shared resource " << id << " not found." << std::endl;
            return nullptr;
        }
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Resource>> uniqueResources_;
    std::unordered_map<std::string, std::shared_ptr<Resource>> sharedResources_;
};

int main() {
    ResourceManager manager;

    manager.addUniqueResource("unique1");
    manager.addUniqueResource("unique2");
    manager.addSharedResource("shared1");
    manager.addSharedResource("shared2");

    manager.useResource("unique1");
    manager.useResource("shared1");

    {
        std::shared_ptr<Resource> sharedPtr = manager.getSharedResource("shared1");
        if (sharedPtr) {
            sharedPtr->use();
        }
    } // sharedPtr goes out of scope but "shared1" is not destroyed since manager still holds a shared pointer

    manager.useResource("unique1");
    manager.useResource("shared1");

    // Demonstrate resource not found
    manager.useResource("unique3");

    return 0;
}
```
