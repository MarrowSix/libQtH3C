cmake_minimum_required(VERSION 3.1)

project(QtH3C
        VERSION 1.0
        LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build ${PROJECT_NAME} as a shared library" ON)
option(USE_CONAN "Use C++ Package Manager Conan" OFF)

set(LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib
    CACHE PATH "Installation directory for libraries")
set(CMAKE_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include
    CACHE PATH "Installation directory for headers")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt5Core 5.5)
find_package(PkgConfig)

if(BUILD_SHARED_LIBS)
    add_definitions(-DQH3C_LIBRARY)
else()
    add_definitions(-DQH3C_STATIC)
endif()

add_subdirectory(lib)
add_subdirectory(qth3c)
