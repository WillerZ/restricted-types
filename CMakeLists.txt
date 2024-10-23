cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(RestrictedTypes C CXX)

include(CTest)

# add_subdirectory(failures)
add_subdirectory(test)
add_subdirectory(demo)
