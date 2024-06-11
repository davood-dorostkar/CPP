# Lambda Function

## Explanation of the Lambda Function

A lambda function in C++ is an anonymous function that can be defined inline and used where a function object or a function pointer is required.

```cpp
[laneID](const Lane &lane) {
    return (laneID == lane.id);
}
```
## Components of the Lambda Function

1. **Capture List (`[laneID]`)**:
   - This part allows the lambda function to capture variables from the surrounding scope. In this case, `laneID` is captured by value.


2. **Parameter List (`(const Lane &lane)`)**:
   - This specifies the parameters that the lambda function takes, just like in a regular function.
   - In this example, the lambda takes a single parameter `lane` of type `const Lane &`.

3. **Function Body (`{ return (laneID == lane.id); }`)**:
   - This is the actual code that the lambda function executes when called.

## How It Works in `std::find_if`

- `std::find_if` takes a range (`lane_list.begin()` to `lane_list.end()`) and a predicate (the lambda function).
- It iterates over the elements in the range and applies the predicate to each element.
- The iteration stops when the predicate returns `true`, and `std::find_if` returns an iterator to that element. If no such element is found, it returns `lane_list.end()`.

```cpp
int laneID = 1;
auto idExists = std::find_if(lane_list.begin(),
                            lane_list.end(), 
                            [laneID](const Lane &lane)
                                {
                                return (laneID == lane.id);
                                }
                            );
```

## Example 

Here’s another simple example to reinforce the syntax:

```cpp
auto add = [](int a, int b) {
    return a + b;
};
```

## Quick Reference for Lambda Syntax

```cpp
[ capture_list ] ( parameter_list ) -> return_type { function_body }
```

- **Capture List**: `[&, x, &y]`
  - `[]` - No capture.
  - `[x, &y]` - Captures `x` by value, `y` by reference.
  - `[=]` - Captures all local variables by value.
  - `[&]` - Captures all local variables by reference.
  
- **Parameter List**: `(int a, int b)`
  - Defines the input parameters like a regular function.

- **Return Type (Optional)**: `-> int`
  - Specifies the return type explicitly if needed. Often deduced automatically.

- **Function Body**: `{ return a + b; }`
  - Contains the logic to execute.