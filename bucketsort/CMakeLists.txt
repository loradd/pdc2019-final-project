cmake_minimum_required(VERSION 3.14.4)
project(bucketsort)

find_package(OpenMP REQUIRED)

# c++11
set (CMAKE_CXX_STANDARD 11)

#headers
include_directories(include)

# sources
file(GLOB SOURCES "src/*.cpp")

# executable
add_executable(main ${SOURCES})

target_link_libraries(main PUBLIC OpenMP::OpenMP_CXX)