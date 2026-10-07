cmake_minimum_required(VERSION 3.20)

project(superAwesomeDemo
    LANGUAGES CXX
)

find_package(superAwesome QUIET)

add_executable(demo
    src/demo.cpp
)

target_link_libraries(demo PRIVATE superAwesome::superAwesomeLibrary)
