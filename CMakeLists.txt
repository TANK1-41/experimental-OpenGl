cmake_minimum_required(VERSION 3.21)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)


find_package(OpenGL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include)
include_directories(${PROJECT_SOURCE_DIR}/src/vender)
include_directories(${PROJECT_SOURCE_DIR}/src)

link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/lib/Release/Win32/)
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-vc2019/)

add_executable(${PROJECT_NAME} src/Application.cpp src/vender/stb_image/stb_image.cpp
        src/vender/imgui/imgui_impl_glfw_gl3.cpp src/vender/imgui/imgui.cpp src/vender/imgui/imgui_demo.cpp src/vender/imgui/imgui_draw.cpp
        src/shader.cpp src/shader.h)
target_link_libraries(${PROJECT_NAME} glew32 glfw3 opengl32)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/res/)
