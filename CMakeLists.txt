cmake_minimum_required(VERSION 3.21)
project(OpenGL)

set(CMAKE_CXX_STANDARD 14)



include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include)
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/lib/Release/Win32/)
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-vc2019/)
#target_link_libraries(${PROJECT_NAME} glew32s, glfw3, opengl123)

# Locate the glfw3 library
#
# This module defines the following variables:
#
# GLFW3_LIBRARY the name of the library;
# GLFW3_INCLUDE_DIR where to find glfw include files.
# GLFW3_FOUND true if both the GLFW3_LIBRARY and GLFW3_INCLUDE_DIR have been found.
#
# To help locate the library and include file, you can define a
# variable called GLFW3_ROOT which points to the root of the glfw library
# installation.
#
# default search dirs
#
# Cmake file from: https://github.com/daw42/glslcookbook

set( _glfw3_HEADER_SEARCH_DIRS
        "${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include")
set( _glfw3_LIB_SEARCH_DIRS
        "${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-vc2019/" )

set( _glew_HEADER_SEARCH_DIRS
        "${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-vc2019/")
set( _glew_LIB_SEARCH_DIRS
        "${PROJECT_SOURCE_DIR}/Dependencies/GLEW/lib/Release/Win32/" )
# Check environment for root search directory
set( _glfw3_ENV_ROOT $ENV{GLFW3_ROOT} )
if( NOT GLFW3_ROOT AND _glfw3_ENV_ROOT )
    set(GLFW3_ROOT ${_glfw3_ENV_ROOT} )
endif()

# Put user specified location at beginning of search
if( GLFW3_ROOT )
    list( INSERT _glfw3_HEADER_SEARCH_DIRS 0 "${GLFW3_ROOT}/include" )
    list( INSERT _glfw3_LIB_SEARCH_DIRS 0 "${GLFW3_ROOT}/lib" )
endif()

# Search for the header
FIND_PATH(GLFW3_INCLUDE_DIR "GLFW/glfw3.h"
        PATHS ${_glfw3_HEADER_SEARCH_DIRS} )

FIND_PATH(GLEW_INCLUDE_DIR "GL/glew.h"
        PATHS ${_glew_HEADER_SEARCH_DIRS} )

# Search for the library
FIND_LIBRARY(GLFW3_LIBRARY NAMES glfw3 glfw
        PATHS ${_glfw3_LIB_SEARCH_DIRS} )

FIND_LIBRARY(GLEW_LIBRARY NAMES glew32s
        PATHS ${_glew_LIB_SEARCH_DIRS} )
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLFW3 DEFAULT_MSG
        GLFW3_LIBRARY GLFW3_INCLUDE_DIR GLEW_LIBRARY GLEW_INCLUDE_DIR)

add_executable(${PROJECT_NAME} src/Application.cpp)
