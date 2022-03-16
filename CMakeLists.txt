cmake_minimum_required(VERSION 3.21)
project(OpenGL)

set(CMAKE_CXX_STANDARD 14)


find_package(OpenGL REQUIRED)
set(CMAKE_C_FLAGS -m32)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include)

link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/lib/Release/Win32/)
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-vc2019/)

add_executable(${PROJECT_NAME} src/Application.cpp src/indexBuffer.cpp src/Renderer.cpp src/Shader.cpp src/texture.cpp src/VertexArray.cpp src/VertexBuffer.cpp src/vender/stb_image/stb_image.cpp)
target_link_libraries(${PROJECT_NAME} glew32 glfw3 opengl32)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/res/)
