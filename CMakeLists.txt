# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(PROJECT_NAME)

# Specify C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add include directories
include_directories(include)

# Add source files
file(GLOB SOURCES "src/*.c")

# Add the executable
add_executable(PROJECT_NAME ${SOURCES})
