cmake_minimum_required(VERSION 3.21)

project(Sandbox VERSION 1.0 LANGUAGES CXX)

add_executable(Sandbox)
target_sources(Sandbox
    PRIVATE
        src/Sandbox.cpp
)
target_compile_features(Qd PUBLIC cxx_std_20)

find_package(Qd REQUIRED)

target_link_libraries(Sandbox PRIVATE Qd::Qd)
