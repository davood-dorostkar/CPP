# VSCode

## vscode options
add `.vscode` directory to the project like:
```
.vscode/
├── c_cpp_properties.json
├── launch.json
├── settings.json
└── tasks.json
```
you can automatically generate files. for example

- for `launch` use `ctrl+shift+p > debug: config`
- for `tasks` use `ctrl+shift+p > tasks: configure task`

## sample debugger options
in the `launch.json` file:

without compiling:
```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "C/C++ Runner: Debug Session",
      "type": "cppdbg",
      "request": "launch",
      "args": [],
      "stopAtEntry": false,
      "externalConsole": false,
      "cwd": "${workspaceFolder}",
      "program": "${workspaceFolder}/bin_file",
      "MIMode": "gdb",
      "miDebuggerPath": "gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ]
    }
  ]
}
```
with compiling (you also need to add a task):
```json
{
  "version": "0.2.0",
  "configurations": [
    // other configs //
    {
    "name": "C/C++ Runner: Debug Session",
    "type": "cppdbg",
    "request": "launch",
    "args": [],
    "stopAtEntry": false,
    "externalConsole": false,
    "cwd": "${workspaceFolder}",
    "program": "${workspaceFolder}/test",
    "MIMode": "gdb",
    "miDebuggerPath": "gdb",
    "preLaunchTask": "Build C++ Debug",
    "setupCommands": [
        {
        "description": "Enable pretty-printing for gdb",
        "text": "-enable-pretty-printing",
        "ignoreFailures": true
        }
    ]
    }
  ]
}
```

## sample tasks options
```json
{
    "version": "2.0.0",
    "tasks": [
      {
        "label": "Build C++ Debug",
        "type": "shell",
        "command": "g++",
        "args": [
          "-g",
          "${workspaceFolder}/test.cpp",
          "-o",
          "${workspaceFolder}/test"
        ],
        "group": {
          "kind": "build",
          "isDefault": true
        },
        "problemMatcher": ["$gcc"],
        "detail": "Generated task to build C++ code"
      }
    ]
  }
  
```