
cmake_minimum_required(VERSION 3.5)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# project name
project(PalletizerX)

# head file path，头文件目录
include_directories(
    "includes", 
)

# the executable
add_executable(PalletizerX ConsoleApplication1.cpp)
