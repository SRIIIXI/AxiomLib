cmake_minimum_required(VERSION 2.8.12)

project(Base64)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/include/)

set(PROJECT_SOURCE_DIR ../../project/src)
set(PROJECT_HEADER_DIR ../../project/include)

set(SOURCE
${SOURCE}
${PROJECT_SOURCE_DIR}/Base64.c
./main.c
)

set(HEADERS
${HEADERS}
${PROJECT_HEADER_DIR}/Base64.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

