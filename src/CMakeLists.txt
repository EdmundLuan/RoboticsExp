
cmake_minimum_required(VERSION 3.5)

# project name
project(PalletizerX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# head file path，头文件目录
include_directories(
    "includes", 
    "oldIncludes",
)

# the executable
add_executable(PalletizerX main.cpp)
