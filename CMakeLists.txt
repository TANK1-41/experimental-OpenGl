cmake_minimum_required(VERSION 3.21)
project(OpenGL)

set(CMAKE_CXX_STANDARD 14)

#find_package(OpenGL REQUIRED)

## Ask the user to give the paths to GLFW, GLEW and GLM.
## On Linux this can be found automatically with pkg-config;
## see http://stackoverflow.com/questions/6889264/cmake-flags-for-opengl-using-glew-and-glfw, for instance.
#
#set(GLFW_INCLUDE_PATH "" CACHE PATH "${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include" )
#set(GLFW_LIBRARY "" CACHE FILEPATH "glfw3" )
#
#set(GLEW_INCLUDE_PATH "" CACHE PATH "${PROJECT_SOURCE_DIR}/Dependencies/GLEW/include" )
#set(GLEW_LIBRARY "" CACHE FILEPATH "glew32s" )
#
#
#set(MY_HEADER_FILES
#        # put all your .h here. Right now we have none.
#        # Example :
#        # ../common/shader.hpp
#        )
#
#set(MY_SOURCE_FILES
#        # put all your .c/.cpp here.
#        src/Application.cpp
#        # ../common/shader.cpp
#        )
#
#
#
#include_directories(
#        ${GLFW_INCLUDE_PATH}
#        ${GLEW_INCLUDE_PATH}
#)
#add_executable(OpenGL
#        ${MY_HEADER_FILES}
#        ${MY_SOURCE_FILES}
#        )
#target_link_libraries(OpenGL
#        ${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
#        ${GLFW_LIBRARY}
#        ${GLEW_LIBRARY}
#        )
#
#
#
#
## HOW-TO. You can safely remove anything below.
#
## test if linux, mac or windows :
#
#if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    message("You're on Mac OS !")
#elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#    message("You're on Linux !")
#elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
#    message("You're on Windows !")
#endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # Yes this is weird but you have to repeat the "if" here.
#
#
## Add a checkbox in CMakeGUI :
#
#set(SOME_STUFF OFF CACHE BOOL "Check this to print an extra message at the beginning of main()")



find_package(OpenGL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include)

link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/lib/Release/Win32)
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-vc2019)

add_executable(${PROJECT_NAME} src/Application.cpp)
target_link_libraries(${PROJECT_NAME} glew32s glfw3 opengl32)

