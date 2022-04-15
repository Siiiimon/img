cmake_minimum_required(VERSION 3.20)
project(img)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/renderer/shader/shader.cpp src/renderer/shader/shader.h
        src/renderer/renderer.cpp src/renderer/renderer.h
        src/ui/log/log.cpp src/ui/log/log.h
        src/app.cpp src/app.h)

# add vendor dependencies
find_package(OpenGL REQUIRED)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/fmt) # maybe exclude this on msvc
add_library(imgui STATIC)
target_sources(imgui PRIVATE
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_tables.cpp
        vendor/imgui/imgui_widgets.cpp
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/backends/imgui_impl_glfw.cpp
        vendor/imgui/backends/imgui_impl_opengl3.cpp)
target_include_directories(imgui PUBLIC
        vendor/imgui
        vendor/imgui/backends)
target_link_libraries(imgui PRIVATE glfw)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        glad
        glm
        fmt
        ${OPENGL_LIBRARIES}
        imgui
)