cmake_minimum_required(VERSION 3.21)

project(Qd VERSION 1.0 LANGUAGES CXX)

include(cmake/FetchContent_spdlog.cmake)

add_library(Qd SHARED)
add_library(Qd::Qd ALIAS Qd)

target_compile_features(Qd PUBLIC cxx_std_20)

target_sources(Qd
    PUBLIC
        include/Qd/Core/Application.h
        include/Qd/Core/Log.h
    INTERFACE
        include/Qd/EntryPoint.h
    PRIVATE
        src/Core/Application.cpp
        src/Core/Log.cpp
)

target_link_libraries(Qd
    PUBLIC
        spdlog::spdlog
)

target_include_directories(Qd
    PRIVATE
        src
    PUBLIC
        include
)
