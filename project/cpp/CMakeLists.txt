cmake_minimum_required(VERSION 3.10.0)

project(CoreLibCpp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

if (WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_NOMINMAX)
endif (WIN32)

include_directories(./include)

set(PROJECT_SOURCE_DIR ./src)
set(PROJECT_HEADER_DIR ./include)

set(SOURCE
${SOURCE}
${PROJECT_SOURCE_DIR}/Base64.cpp
${PROJECT_SOURCE_DIR}/Buffer.cpp
${PROJECT_SOURCE_DIR}/Configuration.cpp
${PROJECT_SOURCE_DIR}/DateTime.cpp
${PROJECT_SOURCE_DIR}/String.cpp
${PROJECT_SOURCE_DIR}/Logger.cpp
${PROJECT_SOURCE_DIR}/ProcessLock.cpp
${PROJECT_SOURCE_DIR}/SignalHandler.cpp
${PROJECT_SOURCE_DIR}/Variant.cpp
${PROJECT_SOURCE_DIR}/StringEx.cpp
${PROJECT_SOURCE_DIR}/CoreLib.cpp
)

set(HEADERS
${HEADERS}
${PROJECT_HEADER_DIR}/Array.hpp
${PROJECT_HEADER_DIR}/Base64.hpp
${PROJECT_HEADER_DIR}/BinaryTree.hpp
${PROJECT_HEADER_DIR}/Buffer.hpp
${PROJECT_HEADER_DIR}/Configuration.hpp
${PROJECT_HEADER_DIR}/DateTime.hpp
${PROJECT_HEADER_DIR}/String.hpp
${PROJECT_HEADER_DIR}/KeyValue.hpp
${PROJECT_HEADER_DIR}/List.hpp
${PROJECT_HEADER_DIR}/Logger.hpp
${PROJECT_HEADER_DIR}/Map.hpp
${PROJECT_HEADER_DIR}/Node.hpp
${PROJECT_HEADER_DIR}/ProcessLock.hpp
${PROJECT_HEADER_DIR}/Queue.hpp
${PROJECT_HEADER_DIR}/SignalHandler.hpp
${PROJECT_HEADER_DIR}/Stack.hpp
${PROJECT_HEADER_DIR}/TreeNode.hpp
${PROJECT_HEADER_DIR}/Variant.hpp
${PROJECT_HEADER_DIR}/VariantType.hpp
${PROJECT_HEADER_DIR}/StringEx.hpp
${PROJECT_HEADER_DIR}/CoreLib.hpp
)

add_library(${PROJECT_NAME}  SHARED ${SOURCE} ${HEADERS})

