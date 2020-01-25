cmake_minimum_required(VERSION 2.8.12)

project(Logger)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/c/include/ ../../project/cpp/include/)

set(SOURCE
${SOURCE}
../../project/c/src/File.c
../../project/c/src/Directory.c
../../project/c/src/Logger.c
../../project/c/src/StringEx.c
./main.c
)

set(HEADERS
${HEADERS}
../../project/c/include/File.h
../../project/c/include/Directory.h
../../project/c/include/Logger.h
../../project/c/include/StringEx.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

