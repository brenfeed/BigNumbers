cmake_minimum_required(VERSION 3.20)
project(123)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(This tests)
get_filename_component(Parent ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
        DOWNLOAD_EXTRACT_TIMESTAMP False
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(Sources
        arithmetics.cpp
        compares.cpp
        constructors.cpp
)

add_executable(${This}
        ${Sources}
        ${Headers}
)

target_link_libraries(${This} PUBLIC
        gtest_main
        BigNumbers
)

target_include_directories(${This} PUBLIC
        ${Parent}
)

add_test(
        NAME ${This}
        COMMAND ${This}
)
