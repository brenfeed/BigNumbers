cmake_minimum_required(VERSION 3.20)
project(123)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(This Project)

option(BUILD_GMOCK "Add GMock for testing" OFF)

set(Sources
        main.cpp
)

add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/BigNumbers
)

add_subdirectory(tests)

add_executable(${This}
        ${Sources}
        ${Headers}
)

target_link_libraries(${This} PUBLIC
        BigNumbers
)
target_include_directories(${This} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
