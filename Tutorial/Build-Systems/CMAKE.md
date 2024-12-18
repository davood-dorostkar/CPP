Always use CMake for projects, not qmake.  

### Subdirs correction
* add a CMakeLists.txt inside main project tree  
* add subprojects to it  
```cmake
cmake_minimum_required(VERSION 3.5)
project(ProjectName LANGUAGES CXX)
add_subdirectory(bin_packing_mip)
```

### Define parameter
```cmake
set(name something)
```
`something` can be an address  

### Add existing libraries inside the system path
```cmake
find_package(Qt5Core)
```

### Add headers directory
```cmake
include_directories(/home/davood/or-tools/include)
```
### Add binaries directory
```cmake
link_directories(/home/davood/or-tools/lib)
```

### Add main project files
```cmake
add_executable(bin_packing_mip  main.cpp)
```

### Add binaries files
```cmake
target_link_libraries(bin_packing_mip Qt5::Core libortools.so)
```
### Select Compiler
to force Cmake to use a specific compiler toolchain when more than one is installed (e.g. in windows we have both mingw and msvc):
```sh
cmake -G "MinGW Makefiles" ..
```
or force more explicitly:
```sh
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
```
