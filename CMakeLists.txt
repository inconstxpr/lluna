cmake_minimum_required(VERSION 3.11)

project (
        lluna
        VERSION 0.1.0
        DESCRIPTION "A game engine."
        LANGUAGES C
)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Build/CMake/Modules ${CMAKE_MODULE_PATH})

option(BUILD_DOCUMENTATION "Build documentation." ON)
option(BUILD_TESTS "Build tests." ON)

add_subdirectory(Source)

if(BUILD_DOCUMENTATION)
        add_subdirectory(Documentation)
endif(BUILD_DOCUMENTATION)

if(BUILD_TESTS)
        enable_testing()
        add_subdirectory(Tests)
endif(BUILD_TESTS)
