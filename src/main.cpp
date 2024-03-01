#include "../include/scop.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  std::cout << "Callback when window change size" << std::endl;
  (void) window;
  glViewport(0, 0, width, height);
}

void error_callback(int error, const char* desc) {
  std::cout << "Error no " << error << " desc : " << desc << std::endl;
}

int main(void) {
  // Starting GLFW
  GLFWwindow* window;
  glfwSetErrorCallback(error_callback);

  std::cout << "Initialization of OpenGL" << std::endl;
  if (!glfwInit())
    exit(1);
  std::cout << "Is glfw Init ?" << std::endl;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//  glfwWindowHint(GFLW_OPENGL_FORWARD_COMPAT, GL_TRUE); Necessary for MacOS
  std::cout << "OpenGL initialization done" << std::endl;

  std::cout << "Creating a window" << std::endl;
  window = glfwCreateWindow(640, 480, "New Window", NULL, NULL);
  if (!window) {
    std::cout << "Error when creating a window" << std::endl;
    glfwTerminate();
    exit(1);
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    exit(1);
  }

  std::cout << "Setting the viewport of the window" << std::endl;
  glViewport(0, 0, 640, 480);
  std::cout << "Enabling callback when resizing window" << std::endl;
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  std::cout << "Starting render loop" << std::endl;
  while (!glfwWindowShouldClose(window)) { //Check if openGL window should close
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return (0);
}
