cmake_minimum_required(VERSION 3.31)
project(LoggerApplication)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/dependencies)
link_directories(${CMAKE_SOURCE_DIR}/dependencies)

add_executable(LoggerApplication main.cpp)

target_link_libraries(LoggerApplication MessageLogger)
