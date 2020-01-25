cmake_minimum_required(VERSION 2.8.12)

project(File)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/include/)

set(PROJECT_SOURCE_DIR ../../project/src)
set(PROJECT_HEADER_DIR ../../project/include)

set(SOURCE
${SOURCE}
../../project/c/src/File.c
./main.c
)

set(HEADERS
${HEADERS}
../../project/c/include/File.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

