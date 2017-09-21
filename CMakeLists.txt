cmake_minimum_required(VERSION 3.7)
project(nse)

if (MSVC)
    #add_compile_options("/std:c++latest")
endif()
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(include)

file(GLOB_RECURSE SOURCE_LIST "source/*.cpp" "include/*.hpp")

add_executable(test_zed "test/main.cpp")

add_executable(test_ads "test/main_ads.cpp")