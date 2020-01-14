cmake_minimum_required(VERSION 2.8.9)

if(POLICY CMP0048)
      cmake_policy(SET CMP0048 NEW)
endif()

project (pascaltriangle VERSION "1.1.0")
configure_file(config.h.in config.h)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(build/pascaltriangle pascal_tri.cpp)
add_executable(build/frame frame.cpp)
