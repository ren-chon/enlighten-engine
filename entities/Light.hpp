#pragma once

#include <glm/ext/vector_float3.hpp>
class Light {
private:
  glm::vec3 position;
  glm::vec3 color;

public:
  Light(glm::vec3 position, glm::vec3 color)
      : position(position), color(color) {}
  glm::vec3 getPosition() const;
  glm::vec3 getColor() const;
  void setPosition(glm::vec3 pos);
  void setColor(glm::vec3 clr);
};