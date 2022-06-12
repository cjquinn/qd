cmake_minimum_required(VERSION 3.21)

project(stb_image VERSION 1.0 LANGUAGES CXX)

add_library(stb_image STATIC)
add_library(stb_image::stb_image ALIAS stb_image)

target_sources(stb_image
    PUBLIC
        include/stb_image/stb_image.h
    PRIVATE
        src/stb_image.cpp
)

target_include_directories(stb_image
    PUBLIC
        include
)
