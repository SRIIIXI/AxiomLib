cmake_minimum_required(VERSION 2.8.12)

project(Map)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/include/)

set(SOURCE
${SOURCE}
../../project/src/Buffer.c
../../project/src/Map.c
./main.c
)

set(HEADERS
${HEADERS}
../../project/include/Buffer.h
../../project/include/Map.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

