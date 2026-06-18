cmake_minimum_required(VERSION 3.10)

# Name of the project
project(turbine_analyzer)

# Require C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# compile the program
add_executable(turbine_analysis main.cpp)

# Use high level of compiler optimistaion
target_compile_options(turbine_analysis PRIVATE "-O3")

# Staticaly link for use in Busybox container
target_link_options(turbine_analysis PRIVATE "-static")
