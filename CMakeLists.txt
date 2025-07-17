cmake_minimum_required(VERSION 3.24)
project(exploding_box_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find all CUDA source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Create executable
add_executable(main ${SOURCES})

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)