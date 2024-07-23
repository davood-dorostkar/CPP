# auto
instead of explicitly specifying variable types (like `int`, `double`, `string`), C++ allows using the `auto` keyword to let the compiler deduce the type automatically.

## Basic Example 
- Instead of writing `int a = 5;`, one can write `auto a = 5;`.
- Similarly, `auto b = a;` deduces that `b` is an `int` because it is assigned from `a`.
```cpp
auto a = "Davood";
auto b = 10.f;
auto c = 5L;
auto d = 4;
auto e = a;
auto f = GetName();
auto g = 'c';
```

## Benefits
- Simplifies code, especially with long or complex types.
- Can make the code cleaner and easier to refactor since you don't have to change the type everywhere if it changes.
```cpp
std::string GetName()
{
    return "davood";
}

int main()
{
    auto name = GetName();
    return 0;
}
```
then if we change the function return type, it still works without any need to change:
```cpp
char* GetName()
{
    return "davood";
}

int main()
{
    auto name = GetName();
    return 0;
}
```

## Drawbacks 
- Can make the code less readable since the type is not explicitly stated.
- Changes in API return types might go unnoticed and could lead to errors. in the code below we will face an error when using `auto` because the deduced size is not compatible with the rest of the code; whereas if we use `std::string` instead, we don't. 
```cpp
char* GetName()
{
    return "davood";
}

int main()
{
    auto name = GetName(); // name is deduced to char*
    int a = name.size(); // error: char* doesnt have size() member
    return 0;
}
```
- using `auto` for simple, well-known types like `int` or `std::string` is not preferred as it can make the code less readable.

## Examples of Appropriate Use


- **Using `auto` with Iterators**: 

Simplifies code when dealing with iterators.
```cpp
std::vector<std::string> strings;
strings.push_back("apple");
strings.push_back("orange");

for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); it++ )
{
    std::cout << *it << std::endl;
}
```
instead we can only write this:
```cpp
for (auto it = strings.begin(); it != strings.end(); it++ )
```

- **Long Type Names**:

For long and complex types, `auto` significantly reduces code verbosity.
```cpp
class Device{};

class DeviceManager
{
private:
    std::unordered_map<std::string, std::vector<Device*>> m_Device;

public:
    const std::unordered_map<std::string, std::vector<Device*>>& GetDevices()
    {
        return m_Device;
    }
};

int main()
{
    DeviceManager dm;

    // the longer way:
    const std::unordered_map<std::string, std::vector<Device*>>& Devices = dm.GetDevices();

    // the shorter way with auto:
    const auto& Devices = dm.GetDevices();
    return 0;
}
```
>Note: Must still use references appropriately (e.g., `const auto&` for non-copying). if you dont use `&` it still works but copies the data, not using as a reference.

## vs using
one other way to simplify the annoying types is with `using`:
```cpp
int main()
{
    using DeviceMap =  std::unordered_map<std::string, std::vector<Device*>>;

    DeviceManager dm;
    const DeviceMap& Devices = dm.GetDevices();

    return 0;
}
```
## vs typedef
another way to simplify the annoying types is with `typedef`:
```cpp
int main()
{
    typedef std::unordered_map<std::string, std::vector<Device*>> DeviceMap;

    DeviceManager dm;
    const DeviceMap& Devices = dm.GetDevices();

    return 0;
}
```

