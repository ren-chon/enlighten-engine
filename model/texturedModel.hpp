#pragma once
#include "model.hpp"
#include "modelTexture.hpp"
class TexturedModel {

private:
  RawModel rawModel;
  ModelTexture texture;

public:
  TexturedModel(const RawModel& model, const ModelTexture& tex);
  // Getters
    RawModel getRawModel() const;
    ModelTexture getTexture() const;
};