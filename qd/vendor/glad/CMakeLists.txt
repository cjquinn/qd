cmake_minimum_required(VERSION 3.21)

project(glad VERSION 1.0 LANGUAGES C)

add_library(glad STATIC)
add_library(glad::glad ALIAS glad)

target_sources(glad
    PUBLIC
        include/glad/glad.h
        include/KHR/khrplatform.h
    PRIVATE
        src/glad.c
)

target_include_directories(glad
    PUBLIC
        include
)
