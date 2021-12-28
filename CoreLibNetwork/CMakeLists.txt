cmake_minimum_required(VERSION 3.5.0)

set(Project CoreLibNetwork)
project(${Project})

set(LIB_VERSION_MAJOR 1)
set(LIB_VERSION_MINOR 0)
set(LIB_VERSION_PATCH 0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PROJECT_SOURCE_DIR ./src)
set(PROJECT_HEADER_DIR ./include)

if (WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
endif(WIN32)

if (WIN32)
    include_directories(${PROJECT_HEADER_DIR} C:/usr/include/ C:/usr/include/CoreLib/ C:/vcpkg/installed/x64-windows/include)
    link_libraries(ws2_32 wsock32 userenv libssl libcrypto CoreLib)    
    link_directories(C:/usr/lib/ C:/vcpkg/installed/x64-windows/lib)
else(WIN32)
    include_directories(${PROJECT_HEADER_DIR} /usr/include/ /usr/local/include/ /usr/local/include/CoreLib)
    link_libraries(rt pthread dl ssl crypto CoreLib)    
    link_directories(/usr/local/lib/ /usr/lib/ /lib/)
endif(WIN32)

set(SOURCE
${SOURCE}
${PROJECT_SOURCE_DIR}/Responder.c
${PROJECT_SOURCE_DIR}/ResponderSsl.c
${PROJECT_SOURCE_DIR}/Mail.c
${PROJECT_SOURCE_DIR}/Imap.c
${PROJECT_SOURCE_DIR}/Smtp.c
)

set(HEADERS
${HEADERS}
${PROJECT_HEADER_DIR}/Responder.h
${PROJECT_HEADER_DIR}/ResponderSsl.h
${PROJECT_HEADER_DIR}/Mail.h
${PROJECT_HEADER_DIR}/Mime.h
${PROJECT_HEADER_DIR}/SecurityType.h
${PROJECT_HEADER_DIR}/Imap.h
${PROJECT_HEADER_DIR}/Smtp.h
)

add_library(${Project} SHARED ${SOURCE} ${HEADERS})

set(CPACK_PACKAGE_FILE_NAME ${Project}.${CMAKE_SYSTEM_PROCESSOR}.${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH})
set(CPACK_PACKAGE_DESCRIPTION, "Core C Network Protocols")

if (WIN32)
set(CPACK_GENERATOR "WIX")
install(TARGETS ${Project} DESTINATION C:/usr/lib)
install(FILES ${HEADERS} DESTINATION C:/usr/include/CoreLib/Network)
else(WIN32)
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Subrato Roy")
install(TARGETS ${Project} DESTINATION local/lib)
install(FILES ${HEADERS} DESTINATION local/include/CoreLib/Network)
endif(WIN32)

include(CPack)


