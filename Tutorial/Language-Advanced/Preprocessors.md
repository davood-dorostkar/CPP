## Avoid multiple inclusion

the standard and compiler safe method:

```cpp
#ifndef CUBE_H
#define CUBE_H
// the header body
#endif
```

the easer and fast-compiled, but non-standard method:

```cpp
#pragma once
// the header body
```
