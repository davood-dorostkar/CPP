# Smart Pointers
smart pointers are wrappers around raw pointers, except they handle memory allocation automatically. they remove the need to `delete` pointers manually.

## std::unique_ptr
- it is a scoped pointer. meaning it will automatically removed if it goes out of scope.
- it cannot be copied. so no more than 1 object cannot point to the same memory location. because when the first object is removed, the second object will remain dangling.
- you can only move the ownership to another object.
- `std::make_unique` is the analogy for `new`
- two ways of defining (the second is preferred):
```cpp
std::unique_ptr<int> ptr(new int());
std::unique_ptr<int> ptr = make_unique<int>();
```
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
- - two ways of defining (the second is preferred):
```cpp
std::shared_ptr<int> ptr(new int());
std::shared_ptr<int> ptr = make_shared<int>();
```
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
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
    std::shared_ptr<MyClass> ptr2 = ptr1;  // ptr2 shares ownership with ptr1

    std::cout << "Reference count: " << ptr1.use_count() << "\n";  // Output: 2

    ptr1->display();
    ptr2->display();

    // Both ptr1 and ptr2 will be destroyed automatically, and the MyClass instance will be deleted
    return 0;
}

```
## std::weak_ptr
- just like the shared pointer, but it is not included in the reference count. so the last shared pointer will free the memory even if there is still a weak pointer left.
- you can define it with assigning to a shared pointer.
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
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
    std::weak_ptr<MyClass> weakPtr = ptr1;  // weakPtr does not increase the reference count

    std::cout << "Reference count: " << ptr1.use_count() << "\n";  // Output: 1

    if (auto sharedPtr = weakPtr.lock()) {  // Convert weakPtr to sharedPtr if the object still exists
        sharedPtr->display();
        std::cout << "Reference count: " << ptr1.use_count() << "\n";  // Output: 2
    } else {
        std::cout << "Object no longer exists\n";
    }

    // ptr1 will be destroyed, and the MyClass instance will be deleted
    return 0;
}
```
## Example
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
