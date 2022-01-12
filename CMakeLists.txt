cmake_minimum_required(VERSION 3.0.2)
project(evolutivos)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

include_directories(
  include
)

add_executable(evolutivos 
  source/subsetsum.cpp
  source/individuo.cpp
  source/populacao.cpp
)
