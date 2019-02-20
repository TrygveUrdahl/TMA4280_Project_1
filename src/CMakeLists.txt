cmake_minimum_required(VERSION 3.1)

project(TMA4280_Project_1 CXX)

add_compile_options(-std=c++17 -O3)

find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(project1 main.cpp zeta0/serialZeta.cpp mach0/serialMach.cpp)

target_link_libraries(project1 OpenMP::OpenMP_CXX ${MPI_LIBRARIES})
