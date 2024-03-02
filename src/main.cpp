#include "../include/scop.hpp"

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

const char *vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  (void) window;
  glViewport(0, 0, width, height);
}

void error_callback(int error, const char* desc) {
  std::cout << "Error no " << error << " desc : " << desc << std::endl;
}

void glfwStarter(glfwStruct* glfw) {
  glfwSetErrorCallback(error_callback);
                                                                             
  if (!glfwInit())
    exit(1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GFLW_OPENGL_FORWARD_COMPAT, GL_TRUE); Necessary for MacOS
                                                                             
  // Creating the window
  glfw->window = glfwCreateWindow(glfw->width, glfw->height, "New Window", NULL, NULL);
  if (!glfw->window) {
    glfwTerminate();
    exit(1);
  }
  glfwMakeContextCurrent(glfw->window);
                                                                             
  // Starting GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    exit(1);
  }
                                                                             
  // Setting the viewport (size in wich openGL will actually draw)
  glViewport(0, 0, glfw->width, glfw->height);
  // Callback for when we resize the window
  glfwSetFramebufferSizeCallback(glfw->window, framebuffer_size_callback);
}

void setupShaders(glfwStruct* glfw) {
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  glfw->shaderProgram = glCreateProgram();
  glAttachShader(glfw->shaderProgram, vertexShader);
  glAttachShader(glfw->shaderProgram, fragmentShader);
  glLinkProgram(glfw->shaderProgram);
  glGetProgramiv(glfw->shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(glfw->shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void buffersAndVertex(unsigned int* VAO) {
  unsigned int VBO, EBO;
  glGenVertexArrays(1, VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
                                                                                
  glBindVertexArray((*VAO));
                                                                                
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

int main(void) {
  glfwStruct glfw;

  glfwStarter(&glfw);
  setupShaders(&glfw);
  buffersAndVertex(&glfw.VAO);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //enable wireframe mode
  // Render loop
  while (!glfwWindowShouldClose(glfw.window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(glfw.shaderProgram);
    glBindVertexArray(glfw.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(glfw.window);
    glfwPollEvents();
  }
  glfwTerminate();
  return (0);
}
