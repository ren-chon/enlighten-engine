# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -O3 -march=native -std=c++17 -I includes/

# Libraries
LIBS = -lglfw -ldl -lGL

# Source files
SRCS = main.cpp includes/glad.c window/windowing.cpp model/loader.cpp model/modelTexture.cpp model/textureLoader.cpp model/texturedModel.cpp model/model.cpp renderer/renderer.cpp shader/shader.cpp shader/staticShader.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = ogl

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Compile the source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run