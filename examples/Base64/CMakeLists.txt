cmake_minimum_required(VERSION 2.8.12)

project(Base64)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/c/include/ ../../project/cpp/include/)

set(SOURCE
${SOURCE}
../../project/c/src/Base64.c
../../project/cpp/src/Base64.cpp
./main.c
)

set(HEADERS
${HEADERS}
../../project/c/include/Base64.h
../../project/cpp/include/Base64.hpp
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

