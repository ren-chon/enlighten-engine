#pragma once

#include "../model/texturedModel.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // For glm::value_ptr
#include <glm/vec3.hpp>         // For glm::vec3
class Entity {
private:
  TexturedModel model;
  glm::vec3 positions;
  float rotX, rotY, rotZ, scale;

public:
  Entity(TexturedModel model, glm::vec3 positions, float rotX, float rotY,
         float rotZ, float scale)
      : model(model), positions(positions), rotX(rotX), rotY(rotY), rotZ(rotZ),
        scale(scale) {}
  void increasePosition(float dx, float dy, float dz) {
    positions.x += dx;
    positions.y += dy;
    positions.z += dz;
  }
  void increaseRotation(float dx, float dy, float dz) {
    rotX += dx;
    rotY += dy;
    rotZ += dz;
  }
  // Getter and Setter for model
  TexturedModel getModel() const { return model; }

  void setModel(const TexturedModel &newModel) { model = newModel; }

  // Getter and Setter for positions
  glm::vec3 getPositions() const { return positions; }

  void setPositions(const glm::vec3 &newPositions) { positions = newPositions; }

  // Getter and Setter for rotX
  float getRotX() const { return rotX; }

  void setRotX(float newRotX) { rotX = newRotX; }

  // Getter and Setter for rotY
  float getRotY() const { return rotY; }

  void setRotY(float newRotY) { rotY = newRotY; }

  // Getter and Setter for rotZ
  float getRotZ() const { return rotZ; }

  void setRotZ(float newRotZ) { rotZ = newRotZ; }

  // Getter and Setter for scale
  float getScale() const { return scale; }

  void setScale(float newScale) { scale = newScale; }
};