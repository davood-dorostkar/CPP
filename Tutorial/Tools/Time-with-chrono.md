```cpp
#include <chrono>


std::chrono::time_point<std::chrono::high_resolution_clock> start;
std::chrono::time_point<std::chrono::high_resolution_clock> end;

start = std::chrono::high_resolution_clock::now();
end = std::chrono::high_resolution_clock::now();

QLOG_DEBUG()<<" Time Interval:"<<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<<" ms";

```