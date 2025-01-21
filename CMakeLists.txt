cmake_minimum_required(VERSION 3.10)

# set the project name
project(SDL2DShmup)

# find system installed SDL
find_package(SDL2 REQUIRED)

# add the executable
add_executable(SDL2DShmup Source/SDL2DShmup.cpp)

# Link SDL to the main executable. SDL also takes care of including the source files.
target_link_libraries(SDL2DShmup SDL2::SDL2 SDL2::SDL2main)