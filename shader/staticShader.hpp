#pragma once
#include "shader.hpp"

class StaticShader : public ShaderProgram {

protected:
    void bindAttributes() override;

public:
    StaticShader();
};
