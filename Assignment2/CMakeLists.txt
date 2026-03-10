cmake_minimum_required(VERSION 4.1)
project(Assignment2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment2
        fuzzylogic.cpp
        fuzzylogic.h
        graphics.cpp
        graphics.h
        main.cpp
        sprites.cpp
        sprites.h
        transform.cpp
        transform.h)
