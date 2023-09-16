cmake_minimum_required(VERSION 3.21)

project(sandbox VERSION 1.0 LANGUAGES CXX)

add_executable(sandbox)
target_sources(sandbox
    PRIVATE
        src/sandbox.cpp
        src/layers/batch_renderer_layer.h
        src/layers/batch_renderer_layer.cpp
        src/layers/sandbox_layer.h
        src/layers/sandbox_layer.cpp
)
target_compile_features(qd PUBLIC cxx_std_20)

find_package(qd REQUIRED)

target_link_libraries(sandbox PRIVATE qd::qd)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
