# CMakeLists.txt
cmake_minimum_required(VERSION 3.20)

# Project metadata
project(FossilTest VERSION 1.1.5 LANGUAGES C CXX)

# Set the C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF) # Ensure strict C11 compliance
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF) # Ensure strict C++20 compliance

# Options
option(WITH_TEST "Enable Fossil Test for this project" OFF)

# Add subdirectory for source code
add_subdirectory(code)
