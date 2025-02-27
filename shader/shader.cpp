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
void ShaderProgram::bindAttribute(int attribute, const std::string &variableName) {
    glBindAttribLocation(programID, attribute, variableName.c_str());
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
    const char* sourcePointer = shaderSource.c_str();
    glShaderSource(shaderID, 1, &sourcePointer, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, nullptr, &infoLog[0]);
        std::cerr << "Shader compilation error (" << filename << "): " << infoLog << std::endl;
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
