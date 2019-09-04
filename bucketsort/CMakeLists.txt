cmake_minimum_required(VERSION 3.14.4)
project(bucketsort)
set(CMAKE_BUILD_TYPE Release)

# headers
include_directories(include)

#sources
file(GLOB utils "src/utils/*.c")
file(GLOB bucketsorts "src/bucketsort/*.c")

# executables
foreach(bucketsort ${bucketsorts})
    get_filename_component(bucketsort_filename ${bucketsort} NAME)
    string(REPLACE ".c" ".out" bucketsort_name ${bucketsort_filename})
    add_executable(${bucketsort_name} ${bucketsort} ${utils})
endforeach(bucketsort ${bucketsorts})
