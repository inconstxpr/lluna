macro(lluna_test test_name source_path)
        add_executable(${test_name} ${source_path})
        target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/Source ${CMAKE_SOURCE_DIR}/Tests)
        target_link_libraries(${test_name} lluna)

        add_test(${test_name} ${test_name})
endmacro(lluna_test test_name source_path)
