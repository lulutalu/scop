#ifndef SCOP_H
  #define SCOP_H

  // Classic C++ libraries
  #include <string>       // IWYU pragma: export
  #include <fstream>      // IWYU pragma: export
  #include <sstream>      // IWYU pragma: export
  #include <iostream>     // IWYU pragma: export
  #include <cmath>        // IWYU pragma: export

  // OpenGL libraries
  #include "glad.h"       // IWYU pragma: export
  #include <GLFW/glfw3.h>

  struct glfwStruct {
    GLFWwindow* window;
    unsigned int shaderProgram[3];
    unsigned int VAO;
    int width = 1000;
    int height = 800;
  };

  class Shader {

    private :

      unsigned int id;

      const char* strVertex;
      const char* strFragment;

    public :

      unsigned int getShaderId();

      Shader(const char* vertexPath, const char* fragmentPath);
      void use();
      void setBool(const std::string &name, bool value) const;
      void setInt(const std::string &name, int value) const;
      void setFloat(const std::string &name, float value) const;

  };

#endif
