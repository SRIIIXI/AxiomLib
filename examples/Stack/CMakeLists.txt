cmake_minimum_required(VERSION 2.8.12)

project(Stack)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/include/)

set(SOURCE
${SOURCE}
../../project/src/Buffer.c
../../project/src/Node.c
../../project/src/Stack.c
./main.c
)

set(HEADERS
${HEADERS}
../../project/include/Buffer.h
../../project/include/Node.h
../../project/include/Stack.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

