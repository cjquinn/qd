cmake_minimum_required(VERSION 3.21)

project(QdProject VERSION 1.0 LANGUAGES CXX)

macro(find_package)
    if (NOT "${ARGV0}" STREQUAL Qd)
        _find_package(${ARGV})
    endif()
endmacro()

add_subdirectory(Qd)
add_subdirectory(Sandbox)
