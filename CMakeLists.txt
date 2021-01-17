cmake_minimum_required(VERSION 3.10)
project(LemonGL)

set(CMAKE_CXX_STANDARD 14)

add_executable(LemonGL main.cpp tga_image.cxx tga_image.hxx geometry.cxx geometry.hxx model.cxx model.hxx texture.cxx texture.hxx shader.hxx utils.cxx utils.hxx)