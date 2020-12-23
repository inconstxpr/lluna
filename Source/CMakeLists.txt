option(BUILD_TOOLS "Build tools." ON)

add_subdirectory(Engine)

if(BUILD_TOOLS)
        add_subdirectory(Tools)
endif(BUILD_TOOLS)
