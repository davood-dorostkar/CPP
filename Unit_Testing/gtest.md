# GTest
## Install in windows
- download
```sh
git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
```
- build configs:

if you installed mingw:
```sh
cmake -G "MinGW Makefiles" ..
```
or if installed msvc:
```sh
cmake -G "Visual Studio 17 2022" ..
```
- make
```sh
make -j6
```
- install to specifc path:
```sh
cmake --install . --prefix "C:/path/to/install"
```
- update Windows ENV PATH
## Install in linux
```sh
sudo apt-get install libgtest-dev
```
## Usage
- in code:
```cpp
#include <gtest/gtest.h>
```
- add to cmake:
```cmake
add_subdirectory(/path/to/googletest)

target_link_libraries(your_project PRIVATE gtest gtest_main)
```
- use directly with gcc:
```sh
g++ your_test_file.cpp -o test_executable -I/path/to/googletest/include -L/path/to/googletest/build/lib -lgtest -lgtest_main -pthread
```
