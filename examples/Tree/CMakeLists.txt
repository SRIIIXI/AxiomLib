cmake_minimum_required(VERSION 2.8.12)

project(Tree)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../../project/include/)

set(SOURCE
${SOURCE}
../../project/src/Buffer.c
../../project/src/TreeNode.c
../../project/src/Tree.c
../../project/src/StringEx.c
./main.c
)

set(HEADERS
${HEADERS}
../../project/include/Buffer.h
../../project/include/TreeNode.h
../../project/include/Tree.h
)

add_executable(${PROJECT_NAME}  ${SOURCE} ${HEADERS})

