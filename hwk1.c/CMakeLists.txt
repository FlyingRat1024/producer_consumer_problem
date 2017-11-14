cmake_minimum_required(VERSION 3.8)
project(hwk1_c)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(hwk1_c ${SOURCE_FILES})

find_package(Threads REQUIRED)
target_link_libraries(hwk1_c Threads::Threads)