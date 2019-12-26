cmake_minimum_required(VERSION 2.8.12)

project(Logger)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/include/)

set(PROJECT_SOURCE_DIR ../../project/src)
set(PROJECT_HEADER_DIR ../../project/include)

set(SOURCE
${SOURCE}
${PROJECT_SOURCE_DIR}/File.c
${PROJECT_SOURCE_DIR}/Directory.c
${PROJECT_SOURCE_DIR}/Logger.c
./main.c
)

set(HEADERS
${HEADERS}
${PROJECT_HEADER_DIR}/File.h
${PROJECT_HEADER_DIR}/Directory.h
${PROJECT_HEADER_DIR}/Logger.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

