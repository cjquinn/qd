cmake_minimum_required(VERSION 3.21)

project(qd_project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

macro(find_package)
    if (NOT "${ARGV0}" STREQUAL qd)
        _find_package(${ARGV})
    endif()
endmacro()

add_subdirectory(qd)
add_subdirectory(sandbox)
