cmake_minimum_required(VERSION 3.1)

project(TMA4280_Project_1 CXX)

SET(CMAKE_CXX_COMPILER "g++-8")
add_compile_options(-std=c++11 -O3)

find_package(MPI REQUIRED)
find_package(OpenMP)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

include_directories(${MPI_INCLUDE_PATH})

add_executable(project1 main.cpp utils.cpp zeta0/serialZeta.cpp mach0/serialMach.cpp
  zeta1/MPIZeta.cpp mach1/MPIMach.cpp zeta2/MPIZeta2.cpp mach2/MPIMach2.cpp
  zeta3/ompZeta.cpp mach3/ompMach.cpp zeta4/hybridZeta.cpp mach4/hybridMach.cpp)

target_link_libraries(project1 ${MPI_LIBRARIES})

if(OpenMP_CXX_FOUND)
    target_link_libraries(project1 PUBLIC OpenMP::OpenMP_CXX)
endif()
