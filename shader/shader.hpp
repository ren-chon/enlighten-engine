#pragma once
#include "../includes/glad/glad.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include <string>
class ShaderProgram {
protected:
  virtual void bindAttributes() = 0;
  int programID; // Now protected so derived classes can access if needed

public:
  ShaderProgram(std::string vshFile, std::string fshFile);
  void linkProgram(); // New method to handle linking
  void start();
  void stop();
  void cleanUp();
  void bindAttribute(int attribute, const std::string &variableName);

private:
  int loadShader(std::string file, int type);
  int vertexShaderID, fragmentShaderID;
};