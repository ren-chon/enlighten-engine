# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -Wall -O3 -march=native -std=c++17 -I includes/
# Libraries
LIBS = -lglfw -ldl -lGL -lassimp
# Source files
SRCS = main.cpp includes/glad.c entities/Light.cpp window/windowing.cpp model/loader.cpp model/modelTexture.cpp model/textureLoader.cpp model/texturedModel.cpp model/model.cpp renderer/renderer.cpp shader/shader.cpp shader/staticShader.cpp entities/entity.cpp entities/camera.cpp renderer/OBJLoader.cpp
# Object files directory
OBJ_DIR = obj
# Object files
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp,$(SRCS))) $(patsubst %.c,$(OBJ_DIR)/%.o,$(filter %.c,$(SRCS)))
# Executable name
TARGET = ogl

# Default target
all: $(OBJ_DIR) $(TARGET)

# Create object directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/window
	mkdir -p $(OBJ_DIR)/model
	mkdir -p $(OBJ_DIR)/renderer
	mkdir -p $(OBJ_DIR)/shader
	mkdir -p $(OBJ_DIR)/entities
	mkdir -p $(OBJ_DIR)/includes

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Compile C++ source files into object files
$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files into object files
$(OBJ_DIR)/%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run