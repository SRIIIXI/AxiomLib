cmake_minimum_required(VERSION 2.8.12)

project(Base64)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/include/)

set(SOURCE
${SOURCE}
../../project/src/Base64.c
./main.c
)

set(HEADERS
${HEADERS}
../../project/include/Base64.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

