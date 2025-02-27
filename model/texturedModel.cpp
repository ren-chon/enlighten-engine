#include "texturedModel.hpp"

// Constructor to initialize rawModel and texture
TexturedModel::TexturedModel(const RawModel& model, const ModelTexture& tex)
    : rawModel(model), texture(tex) { // Use member initializer list
}

// Getter for rawModel
RawModel TexturedModel::getRawModel() const {
    return rawModel;
}

// Getter for texture
ModelTexture TexturedModel::getTexture() const {
    return texture;
}