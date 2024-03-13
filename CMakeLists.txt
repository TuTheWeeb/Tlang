cmake_minimum_required(VERSION 3.25)

project("lang")

set(CMAKE_BUILD_TYPE Debug)
set(COMPILE_FLAGS "${COMPILE_FLAGS} -lm -std=c++23 -j4")

add_executable(${PROJECT_NAME} "src/main.cpp")


