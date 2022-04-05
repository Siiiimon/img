cmake_minimum_required(VERSION 3.20)
project(img)

set(CMAKE_CXX_STANDARD 14)

add_executable(img main.cpp)

# add vendor dependencies
find_package(OpenGL REQUIRED)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        glad
        ${OPENGL_LIBRARIES}
)