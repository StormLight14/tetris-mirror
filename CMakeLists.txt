cmake_minimum_required(VERSION 3.15)
project(MyProject LANGUAGES CXX)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add your source files
add_executable(MyProject main.cpp Game.cpp Piece.cpp)

