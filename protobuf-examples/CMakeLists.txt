# Minimum CMake required
cmake_minimum_required(VERSION 2.8.12)

# Project
project(protobuf-examples)

# Find required protobuf package
find_package(protobuf REQUIRED)

add_definitions(-std=c++11)

include_directories(${PROTOBUF_INCLUDE_DIRS})


set(fslSources
        ./add_person.cc
        ./addressbook.pb.h
        ./addressbook.pb.cc
        )

add_executable(add_person_cpp ${fslSources})

target_link_libraries(add_person_cpp ${PROTOBUF_LIBRARIES})


set(fslSources
        ./list_people.cc
        ./addressbook.pb.h
        ./addressbook.pb.cc
        )

add_executable(list_people_cpp ${fslSources})

target_link_libraries(list_people_cpp ${PROTOBUF_LIBRARIES})
