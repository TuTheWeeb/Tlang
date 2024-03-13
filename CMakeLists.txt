cmake_minimum_required(VERSION 3.25)

project("lang")

set(CMAKE_BUILD_TYPE Debug)
set(COMPILE_FLAGS "${COMPILE_FLAGS} -std=c++23 -j4")

file(GLOB SOURCES "include/*.cpp")

add_executable(${PROJECT_NAME} "src/main.cpp" ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} m)

