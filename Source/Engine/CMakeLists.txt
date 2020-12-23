add_library(lluna STATIC)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
target_include_directories(lluna PUBLIC ${PARENT_DIR})

target_precompile_headers(lluna PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/pch.h)

set_property(TARGET lluna PROPERTY C_STANDARD 99)

# lluna modules.
include(${CMAKE_SOURCE_DIR}/Build/CMake/llunaModules.cmake)

set(ENGINE_MODULES
        Math
)

set(ENGINE_ENABLED_MODULES
        Math
        CACHE STRING "Enabled engine modules."
)

enable_lluna_modules(ENGINE ENGINE_MODULES ENGINE_ENABLED_MODULES)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Modules.h.in ${CMAKE_CURRENT_BINARY_DIR}/Modules.h)
