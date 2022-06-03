cmake_minimum_required(VERSION 3.8)

set(Project Core)
project(${Project})

add_subdirectory(CoreLib)
#add_subdirectory(CoreLibNetwork)
add_subdirectory(CoreTest)

