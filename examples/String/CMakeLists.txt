cmake_minimum_required(VERSION 2.8.12)

project(StringEx)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/include/)

set(PROJECT_SOURCE_DIR ../../project/src)
set(PROJECT_HEADER_DIR ../../project/include)

set(SOURCE
${SOURCE}
${PROJECT_SOURCE_DIR}/StringEx.c
./main.c
)

set(HEADERS
${HEADERS}
${PROJECT_HEADER_DIR}/StringEx.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

