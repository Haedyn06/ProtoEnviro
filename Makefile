# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -I/usr/lib/pkgconfig/../../include -I/usr/local/include/SDL3_ttf -I/usr/local/include/SDL3_mixer -I/usr/local/include/SDL3_image
LDFLAGS := -L/usr/local/lib -lSDL3 -lSDL3_ttf -lSDL3_mixer

# Target executable and source files
TARGET := Playit
SRC := main.cpp
OBJ := $(SRC:.cpp=.o)

# Default build rule
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Rule to compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(TARGET) $(OBJ)

# Run the executable
run: $(TARGET)
	./$(TARGET)
