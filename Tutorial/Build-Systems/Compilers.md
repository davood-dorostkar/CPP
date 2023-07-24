* `Cmake` is a cross-platform solution for building software. it makes a build configuration, then `make` makes the binary.
* there are `scripted` (interpreted) languages that do the compilation in runtime (python, javascript); and compiled languages that compilation and running are separate steps.
* `compiler` makes some `object files`, then `linker` links the object files to the libraries, so they can run.
* `dynamic linking` happens when the linker puts the libraries' references in the program, instead of the libraries themselves. so the binary will be reduced in size.

### build project
```
make
```
clear project build
```
make clean
```
### g++
to compile a source file with g++:
```
g++ source.cpp -o output
```
