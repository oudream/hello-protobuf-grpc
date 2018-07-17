# prepare install protobuf , grpc

# Minimum CMake required
cmake_minimum_required(VERSION 2.8.12)

# Project
project(hello-protobuf-grpc)

add_subdirectory(grpc-helloworld)
add_subdirectory(protobuf-examples)

