cmake_minimum_required(VERSION 2.8.9)

if(POLICY CMP0048)
      cmake_policy(SET CMP0048 NEW)
endif()

#project (EuclideanLength VERSION "1.1.0")
#configure_file(config.h.in config.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("~/git/range-v3/include")
include_directories("/usr/local/include")

add_executable(build/overloadM OverloadMatrix.cpp)
add_executable(build/matrix Matrix.cpp)
add_executable(build/settings_opt Settings_opt.cpp)
add_executable(build/settings Settings.cpp)
add_executable(build/vec_boost_interprocess boost_interprocess_vec.cpp)
add_executable(build/test boost_interprocess_test.cpp)
add_executable(build/set_boostinterprocess set_boost_interprocess_test.cpp)
#add_executable(build/test test.cpp)
