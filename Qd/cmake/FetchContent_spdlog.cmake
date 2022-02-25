cmake_minimum_required(VERSION 3.14)

include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.9.2
)

FetchContent_MakeAvailable(spdlog)
