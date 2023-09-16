cmake_minimum_required(VERSION 3.14)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.6
)

FetchContent_MakeAvailable(glfw)
