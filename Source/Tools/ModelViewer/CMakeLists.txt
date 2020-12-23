add_executable(ModelViewer)

target_link_libraries(ModelViewer lluna)

set_property(TARGET ModelViewer PROPERTY C_STANDARD 99)

# lluna modules.
include(${CMAKE_SOURCE_DIR}/Build/CMake/llunaModules.cmake)

set(MODEL_VIEWER_MODULES
        Launch
)

set(MODEL_VIEWER_ENABLED_MODULES
        Launch
        CACHE STRING "Enabled ModelViewer modules."
)

enable_lluna_modules(MODEL_VIEWER MODEL_VIEWER_MODULES MODEL_VIEWER_ENABLED_MODULES)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Modules.h.in ${CMAKE_CURRENT_BINARY_DIR}/Modules.h)
