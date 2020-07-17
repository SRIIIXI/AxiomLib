cmake_minimum_required(VERSION 2.8.12)

project(File)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/include/)

set(SOURCE
${SOURCE}
../../project/src/File.c
./main.c
)

set(HEADERS
${HEADERS}
../../project/include/File.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

