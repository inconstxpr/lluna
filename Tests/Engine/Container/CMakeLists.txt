include(${CMAKE_SOURCE_DIR}/Build/CMake/llunaTests.cmake)

lluna_test(DynamicArrayTests DynamicArrayTests.c)
lluna_test(RedBlackTreeTests RedBlackTreeTests.c)
lluna_test(StringTests StringTests.c)
