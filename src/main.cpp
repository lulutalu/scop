#include "../include/scop.hpp"

float triangle1[] = {
  // first triangle
  -0.9f, -0.5f, 0.0f,  // left 
  -0.0f, -0.5f, 0.0f,  // right
  -0.45f, 0.5f, 0.0f,  // top
};

float triangle2[] = {
  // second triangle
  0.0f, -0.5f, 0.0f,  // left
  0.9f, -0.5f, 0.0f,  // right
  0.45f, 0.5f, 0.0f   // top
};

unsigned int indices1[] = {
  0, 1, 2
};

unsigned int indices2[] = {
  0, 1, 2
};

const char *vertexShaderSource1 = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

const char *fragmentShaderSource1 = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\0";

const char *vertexShaderSource2 = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  " FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
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
  unsigned int vertexShader[2];
  vertexShader[0] = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader[0], 1, &vertexShaderSource1, NULL);
  glCompileShader(vertexShader[0]);
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader[0], GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader[0], 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  unsigned int fragmentShader[2];
  fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader[0], 1, &fragmentShaderSource1, NULL);
  glCompileShader(fragmentShader[0]);
  glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader[0], 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  glfw->shaderProgram[0] = glCreateProgram();
  glAttachShader(glfw->shaderProgram[0], vertexShader[0]);
  glAttachShader(glfw->shaderProgram[0], fragmentShader[0]);
  glLinkProgram(glfw->shaderProgram[0]);
  glGetProgramiv(glfw->shaderProgram[0], GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(glfw->shaderProgram[0], 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  vertexShader[1] = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader[1], 1, &vertexShaderSource2, NULL);
  glCompileShader(vertexShader[1]);
  glGetShaderiv(vertexShader[1], GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader[1], 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader[1], 1, &fragmentShaderSource2, NULL);
  glCompileShader(fragmentShader[1]);
  glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader[1], 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  glfw->shaderProgram[1] = glCreateProgram();
  glAttachShader(glfw->shaderProgram[1], vertexShader[1]);
  glAttachShader(glfw->shaderProgram[1], fragmentShader[1]);
  glLinkProgram(glfw->shaderProgram[1]);
  glGetProgramiv(glfw->shaderProgram[1], GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(glfw->shaderProgram[1], 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glDeleteShader(vertexShader[0]);
  glDeleteShader(fragmentShader[0]);
  glDeleteShader(vertexShader[1]);
  glDeleteShader(fragmentShader[1]);
}

void buffersAndVertex(unsigned int* VAO) {
  unsigned int VBOs[2];//, EBO;
  glGenVertexArrays(2, VAO);
  glGenBuffers(2, VBOs);
//  glGenBuffers(1, &EBO);
                                                                                
  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


//  glBindBuffer(GL_ARRAY_BUFFER, 0);
//  glBindVertexArray(0);
}

int main(void) {
  glfwStruct glfw;

  glfwStarter(&glfw);
  setupShaders(&glfw);
  buffersAndVertex(glfw.VAOs);

//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //enable wireframe mode
  // Render loop
  while (!glfwWindowShouldClose(glfw.window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(glfw.shaderProgram[0]);
    glBindVertexArray(glfw.VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(glfw.shaderProgram[1]);
    glBindVertexArray(glfw.VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(glfw.window);
    glfwPollEvents();
  }
  glfwTerminate();
  return (0);
}
