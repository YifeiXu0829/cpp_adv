cmake_minimum_required(VERSION 2.8.9)

if(POLICY CMP0048)
      cmake_policy(SET CMP0048 NEW)
endif()

project (projectname VERSION "1.1.0")
#configure_file(config.h.in config.h)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

#SET(CMAKE_CXX_FLAGS "-O0")
#SET(CMAKE_C_FLAGS "-O0")
add_executable(build/test1 DistributedCounterTest1.cpp)
add_executable(build/test2 DistributedCounterTest2.cpp)
add_executable(build/test3 DistributedCounterTest3.cpp)
add_executable(build/test4 DistributedCounterTest4.cpp)
add_executable(build/mat matrixmultiplication.cpp)
#add_executable(build/stack stack.cpp)
