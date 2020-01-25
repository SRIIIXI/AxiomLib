cmake_minimum_required(VERSION 2.8.12)

project(Stack)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/c/include/ ../../project/cpp/include/)

set(SOURCE
${SOURCE}
../../project/c/src/Buffer.c
../../project/c/src/Node.c
../../project/c/src/Stack.c
./main.c
)

set(HEADERS
${HEADERS}
../../project/c/include/Buffer.h
../../project/c/include/Node.h
../../project/c/include/Stack.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

