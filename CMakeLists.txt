cmake_minimum_required(VERSION 3.20)
project(img)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/shader/shader.cpp src/shader/shader.h
)

# add vendor dependencies
find_package(OpenGL REQUIRED)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glm)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/stb)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        glad
        glm
        ${OPENGL_LIBRARIES}
)