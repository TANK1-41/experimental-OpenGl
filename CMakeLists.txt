cmake_minimum_required(VERSION 3.21)
project(OpenGL)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)


include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include)

link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/lib/Release/Win32)
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-vc2019)

add_executable(${PROJECT_NAME} src/Application.cpp)
target_link_libraries(${PROJECT_NAME} glew32s, glfw3, opengl23)

