# Define the compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++20

# Define the target executable and source file
TARGET = main
SRC = main.cpp Game.cpp Piece.cpp

# Default target to build
all: $(TARGET)

# Rule to build the target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) -lncurses

# Clean up build artifacts
clean:
	rm -f $(TARGET)

