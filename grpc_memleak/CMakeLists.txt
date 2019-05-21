# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# cmake build file for C++ helloworld example.
# Assumes protobuf and gRPC have been installed using cmake.
# See cmake_externalproject/CMakeLists.txt for all-in-one cmake build
# that automatically builds all the dependencies before building helloworld.

# prepare : install protobuf , grpc
# prepare : install protobuf , grpc
# prepare : install protobuf , grpc

cmake_minimum_required(VERSION 2.8)

project(randnum C CXX)

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  add_definitions(-D_WIN32_WINNT=0x600)
endif()


#SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-module)

#message('-------------')
#message("\${CMAKE_MODULE_PATH}" ${CMAKE_MODULE_PATH})


# This branch assumes that gRPC and all its dependencies are already installed
# on this system, so they can be located by find_package().

# Find Protobuf installation
# Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

#  set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
#  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
set(_GRPC_CPP_PLUGIN_EXECUTABLE ${GRPC_CPP_PLUGIN})

# Proto file
get_filename_component(hsw_proto "./randnum.proto" ABSOLUTE)
get_filename_component(hsw_proto_path "${hsw_proto}" PATH)

# Generated sources
set(hsw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/randnum.pb.cc")
set(hsw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/randnum.pb.h")
set(hsw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/randnum.grpc.pb.cc")
set(hsw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/randnum.grpc.pb.h")
add_custom_command(
      OUTPUT "${hsw_proto_srcs}" "${hsw_proto_hdrs}" "${hsw_grpc_srcs}" "${hsw_grpc_hdrs}"
      COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hsw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hsw_proto}"
      DEPENDS "${hsw_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Targets randnum_[async_](client|server)
foreach(_target
  randnum_client randnum_server)
  add_executable(${_target} "${_target}.cc"
    ${hsw_proto_srcs}
    ${hsw_grpc_srcs})
  target_link_libraries(${_target}
          ${GRPCPP_LIBRARY}
          ${GRPCPP_LIBRARY_UNSECURE}
          ${GPR_LIBRARY}
    ${PROTOBUF_LIBRARIES})
endforeach()

message("--")
message("\${CMAKE_CURRENT_BINARY_DIR}" ${CMAKE_CURRENT_BINARY_DIR})
message("\${hsw_proto_path}" ${hsw_proto_path})
message("\${_GRPC_CPP_PLUGIN_EXECUTABLE}" ${_GRPC_CPP_PLUGIN_EXECUTABLE})
message("\${hsw_proto}" ${hsw_proto})
message("\${PROTOBUF_PROTOC_EXECUTABLE}" ${PROTOBUF_PROTOC_EXECUTABLE})

message("--")
message("\${GRPCPP_LIBRARY}" ${GRPCPP_LIBRARY})
message("\${GRPCPP_LIBRARY_UNSECURE}" ${GRPCPP_LIBRARY_UNSECURE})
message("\${PROTOBUF_LIBRARIES}" ${PROTOBUF_LIBRARIES})
