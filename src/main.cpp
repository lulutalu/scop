#include "../include/scop.hpp"

int main(void) {
  std::cout << "Creating a window" << std::endl;
  GLFWwindow* window = glfwCreateWindow(640, 480, "New Window", NULL, NULL);
  if (!window) {
    std::cout << "Error when creating a window" << std::endl;
    exit(1);
  }
}
