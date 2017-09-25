cmake_minimum_required(VERSION 3.7)
project(nse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# specifi compiler options
if (MSVC)
    add_compile_options(/wd4710 /std:c++latest /we4309)
else()
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++1z" )
endif()

include_directories(include)

file(GLOB_RECURSE SOURCE_LIST "source/*.cpp" "include/*.hpp")

add_executable(test_zed "test/main.cpp")

add_executable(test_ads "test/main_ads.cpp")