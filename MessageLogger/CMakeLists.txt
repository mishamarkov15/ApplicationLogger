cmake_minimum_required(VERSION 3.31)
project(MessageLogger VERSION 0.1 DESCRIPTION "Library for writing any messages with different levels to journal.")

set(CMAKE_CXX_STANDARD 17)

add_library(MessageLogger SHARED src/library.cpp)

set_target_properties(MessageLogger PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(MessageLogger PROPERTIES PUBLIC_HEADER include/library.h)

target_include_directories(MessageLogger PRIVATE .)

include(GNUInstallDirs)
install(TARGETS MessageLogger
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})