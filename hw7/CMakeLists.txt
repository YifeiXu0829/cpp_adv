cmake_minimum_required(VERSION 2.8.9)

if(POLICY CMP0048)
      cmake_policy(SET CMP0048 NEW)
endif()

#project (EuclideanLength VERSION "1.1.0")
#configure_file(config.h.in config.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_executable(build/sort sort_wrapper.cpp)
add_executable(build/async my_async.cpp)
add_executable(build/pt my_packaged_task.cpp)
add_executable(build/mpf my_promise.cpp)
