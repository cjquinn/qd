cmake_minimum_required(VERSION 3.21)

project(Qd VERSION 1.0 LANGUAGES CXX)

add_library(Qd OBJECT)
add_library(Qd::Qd ALIAS Qd)
target_compile_features(Qd PRIVATE cxx_std_20)

target_sources(Qd
        PRIVATE
            src/Qd.cpp
        )
target_include_directories(Qd PUBLIC include)
