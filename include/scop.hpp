#ifndef SCOP_H
  #define SCOP_H

  #include <iostream> // IWYU pragma: export
  #include "glad.h" // IWYU pragma: export
  #include <GLFW/glfw3.h>

  struct glfwStruct {
    GLFWwindow* window;
    unsigned int shaderProgram[2];
    unsigned int VAOs[2];
    int width = 1000;
    int height = 800;
  };


#endif
