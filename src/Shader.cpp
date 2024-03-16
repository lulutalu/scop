#include "../include/scop.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
  // GLSL shaders strings
  std::string vertexCode;
  std::string fragmentCode;

  // input file stream declaration
  std::ifstream fVertex;
  std::ifstream fFragment;

  // setting up input file stream exceptions
  fVertex.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fFragment.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {

    fVertex.open(vertexPath);
    fFragment.open(fragmentPath);

    if (!fVertex.is_open()) {
      std::cout << "ERROR::SHADER::VERTEX::FILE_OPENING_ERROR" << std::endl;
      exit(1);
    }
    if (!fFragment.is_open()) {
      std::cout << "ERROR::SHADER::FRAGMENT::FILE_OPENING_ERROR" << std::endl;
      exit(1);
    }

    std::stringstream streamVertex, streamFragment;

    streamVertex << fVertex.rdbuf();
    streamFragment << fFragment.rdbuf();

    fVertex.close();
    fFragment.close();

    vertexCode = streamVertex.str();
    fragmentCode = streamFragment.str();

  } catch (const std::ios_base::failure &e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << e.what() << std::endl;
    exit(1);
  }

  this->strVertex = vertexCode.c_str();
  this->strFragment = fragmentCode.c_str();

  // Declaration of variable for shaders compilation
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  // Compilation of vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &this->strVertex, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // Compilation of fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &this->strFragment, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // Creation of shader program
  this->id = glCreateProgram();
  glAttachShader(this->id, vertex);
  glAttachShader(this->id, fragment);
  glLinkProgram(this->id);

  glGetProgramiv(this->id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->id, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  // Deletion of the shaders cause they're now linked into the program
  glDeleteShader(vertex);
  glDeleteShader(fragment);

}

void Shader::use() {
  glUseProgram(this->id);
}

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
}

unsigned int Shader::getShaderId() {
  return this->id;
}
