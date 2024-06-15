cmake_minimum_required(VERSION 3.20)
project(123)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(This BigNumbers)

set(Sources
        BigFloat.cpp
        BigInteger.cpp

)
set(Headers
        BigFloat.h
        BigInteger.h
)

add_library(${This} SHARED
        ${Sources}
        ${Headers}
)
