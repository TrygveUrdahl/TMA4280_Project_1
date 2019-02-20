cmake_minimum_required(VERSION 3.1)

project(TMA4280_Project_1 CXX)


add_compile_options(-std=c++17 -O3)
#SET(CMAKE_CXX_COMPILER "/usr/local/Cellar/gcc/8.2.0/bin/c++-8")

find_package(OpenMP REQUIRED)
add_executable(main main.cpp utils.cpp latticegenerator.cpp percolate.cpp)
target_link_libraries(main PRIVATE OpenMP::OpenMP_CXX)
