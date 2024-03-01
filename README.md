# scop
 This mini project is a first step towards the use of OpenGL.
 One of the first project inside of the Graphics branch at 42.

## Libraries
 To ensure the proper functioning of the program, you must have the following libraries installed:

 ```bash
 sudo apt-get install cmake xorg-dev libglu1-mesa-dev
 ```

 You should now have :
 ```bash
 /usr/include/GL
 /usr/lib/x86_64-linux-gnu/libGL.so
 ```

 Then to use GLFW, it is encouraged to install it from the source code. This is to be sure you have the latest version as well as the proper version for your system.
 You can find it [here](https://www.glfw.org).
 Then, unzip the package and run the following commands:
 ```bash
 cd glfw-x.x.x
 rehash
 cmake -G "Unix Makefiles"
 make
 sudo make install
 ```

 You should now have :
 ```bash
 /usr/local/include/GLFW
 /usr/local/lib/libglfw3.a
 ```

## Compilation

Now all you need is to include the library in your project.
```c
#include <GLFW/glfw3.h>
```

And you might wanna link the library when compiling:
```bash
-lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread
```
Note :
If it's installed on your machine, it's recommended to use pkg-config to know how to link and include the library for compilation.<br>

Add to CXXFLAGS :
```bash
pkg-config --cflags glfw3
```

Add to LINKFLAGS :
```bash
pkg-config --static --libs glfw3
```

## Source

[Explanation for installation](https://web.eecs.umich.edu/~sugih/courses/eecs487/glut-howto/glfw/)
[Explanation for Compilation](https://www.glfw.org/docs/latest/build_guide.html#build_link_pkgconfig)
