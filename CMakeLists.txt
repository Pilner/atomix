# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(Atomix)

# Specify C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add include directories
include_directories(include)

# Add source files
file(GLOB SOURCES "src/*.c")

# Add the executable
add_executable(atomix ${SOURCES})

# Set the output directory to the previous directory
# set_target_properties(atomix PROPERTIES
# 	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.."
# )
