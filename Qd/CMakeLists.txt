cmake_minimum_required(VERSION 3.21)

project(Qd VERSION 1.0 LANGUAGES CXX)

include(cmake/FetchContent_glfw.cmake)
include(cmake/FetchContent_spdlog.cmake)

add_subdirectory(vendor/glad)

find_package(OpenGL REQUIRED)

add_library(Qd STATIC)
add_library(Qd::Qd ALIAS Qd)

target_compile_features(Qd PUBLIC cxx_std_20)

target_sources(Qd
    PUBLIC
        include/Qd/Application.h
        include/Qd/Core/Assert.h
        include/Qd/Core/Base.h
        include/Qd/Core/Codes.h
        include/Qd/Core/Layer.h
        include/Qd/Core/Log.h
        include/Qd/Events/Event.h
        include/Qd/Events/KeyboardEvent.h
        include/Qd/Events/MouseEvent.h
        include/Qd/Events/WindowEvent.h
    INTERFACE
        include/Qd/EntryPoint.h
        include/Qd/Store/Action.h
        include/Qd/Store/Reducer.h
        include/Qd/Store/Store.h
    PRIVATE
        src/Application.cpp
        src/Core/Layer.cpp
        src/Core/LayerStack.h
        src/Core/LayerStack.cpp
        src/Core/Log.cpp
        src/Core/Window.h
        src/Core/Window.cpp
)

target_include_directories(Qd
    PRIVATE
        src
    PUBLIC
        include
)

target_link_libraries(Qd
    PUBLIC
        spdlog::spdlog
    PRIVATE
        glad::glad
        glfw
        OpenGL::GL
)
