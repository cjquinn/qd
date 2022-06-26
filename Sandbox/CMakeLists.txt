cmake_minimum_required(VERSION 3.21)

project(Sandbox VERSION 1.0 LANGUAGES CXX)

add_executable(Sandbox)
target_sources(Sandbox
    PRIVATE
        src/Sandbox.cpp
        src/Layers/BatchRendererLayer.h
        src/Layers/BatchRendererLayer.cpp
        src/Layers/SandboxLayer.h
        src/Layers/SandboxLayer.cpp
)
target_compile_features(Qd PUBLIC cxx_std_20)

find_package(Qd REQUIRED)

target_link_libraries(Sandbox PRIVATE Qd::Qd)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
