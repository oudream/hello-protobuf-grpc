# prepare install protobuf , grpc

# Minimum CMake required
cmake_minimum_required(VERSION 3.0)

# Project
project(hello-protobuf-grpc)

#set(GRPC_AS_SUBMODULE 1)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#add_subdirectory(grpc)
if (GRPC_AS_SUBMODULE)
    add_subdirectory(grpc/examples/cpp/helloworld)
else()
    add_subdirectory(grpc-helloworld)
    add_subdirectory(grpc-hellostreamingworld)
    add_subdirectory(grpc_memleak)
    add_subdirectory(protobuf-examples)
endif ()

