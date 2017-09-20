cmake_minimum_required(VERSION 3.1)

project(nse)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(include)

file(GLOB_RECURSE SOURCE_LIST "source/*.cpp" "include/*.hpp")

add_executable(nse ${SOURCE_LIST})

set_target_properties(nse
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "bin"
        OUTPUT_NAME  "nse"
        )
