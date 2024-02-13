cmake_minimum_required(VERSION 3.27)
project(2048 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(2048
        main.c)
