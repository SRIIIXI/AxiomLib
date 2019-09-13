cmake_minimum_required(VERSION 2.8.12)

project(List)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/headers/)

set(PROJECT_SOURCE_DIR ../../project/sources)
set(PROJECT_HEADER_DIR ../../project/headers)

set(SOURCE
${SOURCE}
${PROJECT_SOURCE_DIR}/Node.c
${PROJECT_SOURCE_DIR}/KeyValue.c
${PROJECT_SOURCE_DIR}/Tree.c
${PROJECT_SOURCE_DIR}/List.c
${PROJECT_SOURCE_DIR}/Map.c
${PROJECT_SOURCE_DIR}/Queue.c
${PROJECT_SOURCE_DIR}/Stack.c
${PROJECT_SOURCE_DIR}/Base64.c
${PROJECT_SOURCE_DIR}/StringEx.c
./main.c
)

set(HEADERS
${HEADERS}
${PROJECT_HEADER_DIR}/Node.h
${PROJECT_HEADER_DIR}/KeyValue.h
${PROJECT_HEADER_DIR}/Tree.h
${PROJECT_HEADER_DIR}/List.h
${PROJECT_HEADER_DIR}/Map.h
${PROJECT_HEADER_DIR}/Queue.h
${PROJECT_HEADER_DIR}/Stack.h
${PROJECT_HEADER_DIR}/Base64.h
${PROJECT_HEADER_DIR}/StringEx.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

