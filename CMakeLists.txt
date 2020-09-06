cmake_minimum_required(VERSION 3.5.0)

set(Project CoreLib)
project(${Project})

set(LIB_VERSION_MAJOR 1)
set(LIB_VERSION_MINOR 0)
set(LIB_VERSION_PATCH 0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(./include /usr/include /usr/local/include)

set(PROJECT_SOURCE_DIR ./src)
set(PROJECT_HEADER_DIR ./include)

set(SOURCE
${SOURCE}
${PROJECT_SOURCE_DIR}/Base64.c
${PROJECT_SOURCE_DIR}/Buffer.c
${PROJECT_SOURCE_DIR}/KeyValue.c
${PROJECT_SOURCE_DIR}/List.c
${PROJECT_SOURCE_DIR}/Queue.c
${PROJECT_SOURCE_DIR}/Stack.c
${PROJECT_SOURCE_DIR}/StringEx.c
${PROJECT_SOURCE_DIR}/StringList.c
${PROJECT_SOURCE_DIR}/File.c
${PROJECT_SOURCE_DIR}/Directory.c
${PROJECT_SOURCE_DIR}/Logger.c
${PROJECT_SOURCE_DIR}/SignalHandler.c
${PROJECT_SOURCE_DIR}/Responder.c
${PROJECT_SOURCE_DIR}/Environment.c
${PROJECT_SOURCE_DIR}/Configuration.c
${PROJECT_SOURCE_DIR}/DateTime.c
${PROJECT_SOURCE_DIR}/Variant.c
${PROJECT_SOURCE_DIR}/CoreLib.c
)

set(HEADERS
${HEADERS}
${PROJECT_HEADER_DIR}/Base64.h
${PROJECT_HEADER_DIR}/Buffer.h
${PROJECT_HEADER_DIR}/KeyValue.h
${PROJECT_HEADER_DIR}/List.h
${PROJECT_HEADER_DIR}/Queue.h
${PROJECT_HEADER_DIR}/Stack.h
${PROJECT_HEADER_DIR}/StringEx.h
${PROJECT_HEADER_DIR}/StringList.h
${PROJECT_HEADER_DIR}/File.h
${PROJECT_HEADER_DIR}/Directory.h
${PROJECT_HEADER_DIR}/Logger.h
${PROJECT_HEADER_DIR}/SignalHandler.h
${PROJECT_HEADER_DIR}/Responder.h
${PROJECT_HEADER_DIR}/Environment.h
${PROJECT_HEADER_DIR}/Configuration.h
${PROJECT_HEADER_DIR}/DateTime.h
${PROJECT_HEADER_DIR}/Variant.h
${PROJECT_HEADER_DIR}/CoreLib.h
)

add_executable(coretest ${SOURCE} ${HEADERS} ./test/main.c)
add_library(core SHARED ${SOURCE} ${HEADERS})

install(TARGETS core DESTINATION local/lib)
install(FILES ${HEADERS} DESTINATION local/include/CoreLib)

install(TARGETS core DESTINATION local/lib)
install(FILES ${HEADERS} DESTINATION local/include/CoreLib)
set(CPACK_PACKAGE_FILE_NAME ${Project}.${CMAKE_SYSTEM_PROCESSOR}.${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH})
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Subrato Roy")
set(CPACK_PACKAGE_DESCRIPTION, "CoreLib C utilities")

include(CPack)


