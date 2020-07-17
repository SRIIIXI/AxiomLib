cmake_minimum_required(VERSION 2.8.12)

project(Directory)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/include/)

set(SOURCE
${SOURCE}
../../project/src/Directory.c
./main.c
)

set(HEADERS
${HEADERS}
../../project/include/Directory.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

