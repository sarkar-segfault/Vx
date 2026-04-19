# Vx
Vx is _a windowing library for simpletons and wizards alike_. For beginners, it is relatively easy to use, and for pros it is easy to do advanced work.

## Features
This project was originally made to compete with the 8-hour OpenGL tutorial standard: [GLFW](https://github.com/glfw/glfw). The design was also inspired by [RGFW](https://github.com/ColleagueRiley/RGFW). Here are some improvements I made from the inspirations:

1. Uses pure C99, and utilizes features like structured literals and enums.
2. Uses an actually structured naming convention - `VxEventKey_0` instead of `GLFW_KEY_0` or `RGFW_key0`.
3. Uses a circular queue/ring buffer event system, so you don't have to be a slave to callbacks.
4. Uses ANGLE OpenGL ES with the native graphics layer for context management.
5. Uses thread-safe design with no exposed globals.

## Example
Here is some example code to get you familiar with the API (you can consult the headers in `Headers/Vx` and the `Tests` directory for more usage examples):

```c
#include "Vx/Vx.h"

int main(void) {
  VxContext *context = NULL;
  VxContext_Create(&context);

  VxWindow *window = NULL;
  VxWindow_Create(&window, context, 0);

  while (VxWindow_IsOpen(window)) {
    VxWindow_PollEvents(window);
  }

  VxWindow_Delete(&window);
  VxContext_Delete(&context);
}
```

Error and event handling are omitted for brevity.

## Build
This project uses [CMake](https://github.com/Kitware/CMake) to build. You can build it via the following command:

```bash
cmake -S. -Bbuild
cmake --build build
```

You can specify a generator of your choice, and set any options defined in `CMakeLists.txt`.

## License
This project is licensed under the [MIT license](https://opensource.org/license/MIT).

## Contributions
Anyone is free to contribute to my spaghetti code, but you have to follow a few rules:

1. Before submission, format your code using `clang-format` with the `.clang-format` file in the root directory.
2. Before submission, check whether your code works on both MSVC and MSYS2 Clang.
3. Before making an issue, check if a similar issue already exists.
