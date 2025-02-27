#pragma once
#include "../includes/glad/glad.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // For glm::vec3
#include <glm/gtc/type_ptr.hpp> // For glm::value_ptr
#include <iostream>
#include <sstream>

#include <string>
class ShaderProgram {
protected:
  virtual void bindAttributes() = 0;
  virtual void locateAllUniformLocations() = 0;
  int programID; // Now protected so derived classes can access if needed

public:
  ShaderProgram(std::string vshFile, std::string fshFile);
  void linkProgram(); // New method to handle linking
  void start();
  void stop();
  void cleanUp();
  void bindAttribute(int attribute, const std::string &variableName);
  int locateUniform(std::string uniformName);
  void loadFloat(int location, float value);
  void loadVector(int location, glm::vec3 value);
  void loadBool(int location, bool value);
  void loadMat4(int location, glm::mat4 value);

private:
  int loadShader(std::string file, int type);
  int vertexShaderID, fragmentShaderID;
};