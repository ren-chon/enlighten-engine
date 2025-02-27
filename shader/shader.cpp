#include "shader.hpp"

void ShaderProgram::start() {
  if (programID != 0) {
    glUseProgram(programID);
  }
}
void ShaderProgram::stop() { glUseProgram(0); }
void ShaderProgram::cleanUp() {
  stop();
  glDetachShader(programID, vertexShaderID);
  glDetachShader(programID, fragmentShaderID);
  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);
  glDeleteProgram(programID);
}
void ShaderProgram::bindAttribute(int attribute,
                                  const std::string &variableName) {
  glBindAttribLocation(programID, attribute, variableName.c_str());
}
int ShaderProgram::locateUniform(std::string uniformName) {
  return glGetUniformLocation(programID, uniformName.c_str());
}
// populate uniform
void ShaderProgram::loadFloat(int location, float value) {
  glUniform1f(location, value);
}
void ShaderProgram::loadVector(int location, glm::vec3 value) {
  glUniform3f(location, value.x, value.y, value.z);
}
void ShaderProgram::loadBool(int location, bool value) {
  float toLoad = 0;
  if (value) {
    toLoad = 1;
  }
  glUniform1f(location, toLoad);
}
void ShaderProgram::loadMat4(int location, glm::mat4 value) {
  // Upload the matrix to the shader uniform
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
int ShaderProgram::loadShader(std::string filename, int type) {
  std::string shaderSource;
  std::ifstream shaderStream(filename, std::ios::in);

  if (shaderStream.is_open()) {
    std::stringstream sstr;
    sstr << shaderStream.rdbuf();
    shaderSource = sstr.str();
    shaderStream.close();
  } else {
    std::cerr << "Could not read file: " << filename << std::endl;
    return 0;
  }

  GLuint shaderID = glCreateShader(type);
  const char *sourcePointer = shaderSource.c_str();
  glShaderSource(shaderID, 1, &sourcePointer, nullptr);
  glCompileShader(shaderID);

  GLint success;
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shaderID, 512, nullptr, &infoLog[0]);
    std::cerr << "Shader compilation error (" << filename << "): " << infoLog
              << std::endl;
    glDeleteShader(shaderID);
    return 0;
  }

  return shaderID;
}

ShaderProgram::ShaderProgram(std::string vshFile, std::string fshFile) {
  vertexShaderID = loadShader(vshFile, GL_VERTEX_SHADER);
  fragmentShaderID = loadShader(fshFile, GL_FRAGMENT_SHADER);

  if (vertexShaderID == 0 || fragmentShaderID == 0) {
    std::cerr << "Failed to load shaders." << std::endl;
    return;
  }

  programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);
  GLint success;
  glGetProgramiv(programID, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(programID, 512, nullptr, &infoLog[0]);
    std::cerr << "Shader program linking error: " << infoLog << std::endl;
    glDeleteProgram(programID);
    programID = 0;
  }
}
void ShaderProgram::linkProgram() {
  bindAttributes(); // Bind attributes BEFORE linking
  glLinkProgram(programID);
  locateAllUniformLocations();

  GLint success;
  glGetProgramiv(programID, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(programID, 512, nullptr, &infoLog[0]);
    std::cerr << "Shader program linking error: " << infoLog << std::endl;
    glDeleteProgram(programID);
    programID = 0;
  }
}
