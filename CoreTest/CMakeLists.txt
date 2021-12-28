cmake_minimum_required(VERSION 3.5.0)

set(Project CoreTest)
project(${Project})

set(LIB_VERSION_MAJOR 1)
set(LIB_VERSION_MINOR 0)
set(LIB_VERSION_PATCH 0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
endif(WIN32)

if (WIN32)
    include_directories(${PROJECT_HEADER_DIR} C:/usr/include/ C:/usr/include/CoreLib/ C:/usr/include/CoreLibNetwork/)
    link_libraries(ws2_32 wsock32 userenv libssl libcrypto CoreLib CoreLibNetwork)    
    link_directories(C:/usr/lib/ C:/vcpkg/installed/x64-windows/lib)
else(WIN32)
    include_directories(${PROJECT_HEADER_DIR} /usr/include/ /usr/local/include/)
    link_libraries(rt pthread dl ssl crypto CoreLib CoreLibNetwork)    
    link_directories(/usr/local/lib/ /usr/lib/ /lib/)
endif(WIN32)

add_executable(${Project} ./main.c)
add_executable(${Project}Network ./netmain.c)



