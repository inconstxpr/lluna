find_package(Doxygen REQUIRED)
find_package(Sphinx REQUIRED)

# All public headers.
file(GLOB_RECURSE LLUNA_HEADERS ${CMAKE_SOURCE_DIR}/Source/**/*.h)

# All documentation files.
file(GLOB_RECURSE LLUNA_DOCUMENTATION_FILES
        ${CMAKE_SOURCE_DIR}/Documentation/**/*.rst
        ${CMAKE_SOURCE_DIR}/Documentation/*.rst
)

# Doxygen variables.
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
set(DOXYGEN_INPUT_DIR ${CMAKE_SOURCE_DIR}/Source)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/Doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)

# Sphinx variables.
set(SPHINX_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/Sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_OUTPUT_DIR}/index.html)

configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)
file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

add_custom_command(
        OUTPUT ${DOXYGEN_INDEX_FILE}
        DEPENDS ${LLUNA_HEADERS}
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
        COMMENT "Generating xml documentation with Doxygen."
        VERBATIM
)
add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})

add_custom_command(
        OUTPUT ${SPHINX_INDEX_FILE}
        COMMAND ${SPHINX_EXECUTABLE} -b html
                -Dbreathe_projects.lluna=${DOXYGEN_OUTPUT_DIR}/xml
                ${SPHINX_INPUT_DIR} ${SPHINX_OUTPUT_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS
                ${LLUNA_DOCUMENTATION_FILES}
                ${DOXYGEN_INDEX_FILE}
        MAIN_DEPENDENCY ${SPHINX_INPUT_DIR}/conf.py
        COMMENT "Generating html documentation with Sphinx."
)
add_custom_target(Sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})
