cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(Project examples)
project(${Project})


add_subdirectory(Base64)
add_subdirectory(List)
add_subdirectory(Map)
add_subdirectory(Queue)
add_subdirectory(Stack)
add_subdirectory(String)
add_subdirectory(Tree)
add_subdirectory(Logger)



