cmake_minimum_required(VERSION 2.8.12)

project(Map)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/c/include/ ../../project/cpp/include/)

set(SOURCE
${SOURCE}
../../project/c/src/Buffer.c
../../project/c/src/Map.c
./main.c
)

set(HEADERS
${HEADERS}
../../project/c/include/Buffer.h
../../project/c/include/Map.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

