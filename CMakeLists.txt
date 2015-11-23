cmake_minimum_required(VERSION 3.3)
project(capnp_error)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp sample.capnp.c++)
add_executable(capnp_error ${SOURCE_FILES})