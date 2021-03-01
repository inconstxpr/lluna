set(ENGINE_CONTAINER_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/DynamicArray.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Private/RedBlackTree.c
)

target_sources(lluna PRIVATE ${ENGINE_CONTAINER_SOURCES})
