set(ENGINE_MATH_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/FloatUtils.c
)

target_sources(lluna PRIVATE ${ENGINE_MATH_SOURCES})
