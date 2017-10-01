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

# include nk libraries
include_directories(include ../../nk/nds/include)
include_directories(include ../../nk/ndb/include)

file(GLOB_RECURSE SOURCE_LIST "source/*.cpp" "include/*.hpp")

# test
add_executable(test_zed "test/main.cpp")
add_executable(test_ads "test/main_ads.cpp")

add_executable(test_table "test/table.cpp")
set_target_properties(test_table PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../test/table")

# bench
include_directories(extlib/benchmark/include)
add_executable(bench_sql_nse test/bench.cpp test/sqlite/sqlite3.c)
target_link_libraries(bench_sql_nse "../extlib/benchmark/lib/benchmark" shlwapi)
set_target_properties(bench_sql_nse PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../test/bench")