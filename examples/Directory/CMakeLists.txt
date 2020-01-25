cmake_minimum_required(VERSION 2.8.12)

project(Directory)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/c/include/ ../../project/cpp/include/)

set(SOURCE
${SOURCE}
../../project/c/src/Directory.c
./main.c
)

set(HEADERS
${HEADERS}
../../project/c/include/Directory.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

