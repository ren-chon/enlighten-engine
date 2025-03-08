#pragma once
#include "../includes/glad/glad.h"
#include "../window/windowing.hpp"
#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // For glm::value_ptr
#include <glm/vec3.hpp>         // For glm::vec3

class Camera {
private:
  glm::vec3 position = glm::vec3(0.0);
  float pitch, yaw, roll;

public:
  void move(GLFWwindow *window);
  float getPitch() const { return pitch; }
  float getYaw() const { return yaw; }
  float getRoll() const { return roll; }
  glm::vec3 getPosition() const { return position; }
};