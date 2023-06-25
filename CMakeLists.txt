cmake_minimum_required(VERSION 3.1)
project(calc LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(clang_tidy)

find_package(raylib CONFIG REQUIRED)
find_package(EnTT   CONFIG REQUIRED)
find_package(FMT    CONFIG REQUIRED)

set(calc_ExternalLibraries
    raylib
    EnTT::EnTT
    fmt::fmt
)

add_subdirectory(calc)