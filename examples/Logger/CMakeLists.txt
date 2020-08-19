cmake_minimum_required(VERSION 2.8.12)

project(Logger)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/include/)

set(SOURCE
${SOURCE}
../../project/src/File.c
../../project/src/Directory.c
../../project/src/Logger.c
../../project/src/StringEx.c
../../project/src/StringList.c
./main.c
)

set(HEADERS
${HEADERS}
../../project/include/File.h
../../project/include/Directory.h
../../project/include/Logger.h
../../project/include/StringEx.h
../../project/include/StringList.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

