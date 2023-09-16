cmake_minimum_required(VERSION 3.21)

project(qd VERSION 1.0 LANGUAGES CXX)

include(cmake/FetchContent_glfw.cmake)
include(cmake/FetchContent_glm.cmake)
include(cmake/FetchContent_spdlog.cmake)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/stb_image)

find_package(OpenGL REQUIRED)

add_library(qd STATIC)
add_library(qd::qd ALIAS qd)

target_compile_features(qd PUBLIC cxx_std_20)

target_sources(qd
    PUBLIC
        include/qd/application.h
        include/qd/core/assert.h
        include/qd/core/base.h
        include/qd/core/codes.h
        include/qd/core/layer.h
        include/qd/core/log.h
        include/qd/events/event.h
        include/qd/events/keyboard_event.h
        include/qd/events/mouse_event.h
        include/qd/events/window_event.h
        include/qd/renderer/camera.h
        include/qd/renderer/render_command.h
        include/qd/renderer/renderer.h
        include/qd/renderer/shader.h
        include/qd/renderer/texture.h
        include/qd/renderer/vertex_array.h
    INTERFACE
        include/qd/entry_point.h
        include/qd/store/action.h
        include/qd/store/reducer.h
        include/qd/store/store.h
    PRIVATE
        src/application.cpp
        src/core/layer.cpp
        src/core/layer_stack.h
        src/core/layer_stack.cpp
        src/core/log.cpp
        src/core/window.h
        src/core/window.cpp
        src/renderer/buffer.h
        src/renderer/buffer.cpp
        src/renderer/camera.cpp
        src/renderer/render_command.cpp
        src/renderer/renderer.cpp
        src/renderer/shader.cpp
        src/renderer/texture.cpp
        src/renderer/vertex_array.cpp
)

target_include_directories(qd
    PRIVATE
        src
    PUBLIC
        include
)

target_link_libraries(qd
    PUBLIC
        glm::glm
        spdlog::spdlog
    PRIVATE
        glad::glad
        glfw
        OpenGL::GL
        stb_image::stb_image
)
