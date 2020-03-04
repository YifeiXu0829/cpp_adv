cmake_minimum_required(VERSION 2.8.9)

if(POLICY CMP0048)
      cmake_policy(SET CMP0048 NEW)
endif()

#project (EuclideanLength VERSION "1.1.0")
#configure_file(config.h.in config.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("~/git/range-v3/include")

add_executable(build/ranges_lib_4 ranges_lib_test_part4.cpp)
add_executable(build/ranges_lib_3 ranges_lib_test_part3.cpp)
add_executable(build/ranges_lib_2 ranges_lib_test_part2.cpp)
add_executable(build/ranges_lib_1 ranges_lib_test_part1.cpp)
add_executable(build/btree btree.cpp)
add_executable(build/test test.cpp)
