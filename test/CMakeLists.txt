project(radix-tree-test)
set(test-srcs test-radix-tree.cxx)
add_executable(radix-test ${test-srcs})
target_link_libraries(radix-test radix-tree compiler-flags GTest::gtest_main)
add_custom_command(
  TARGET radix-test
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:radix-test>"
          "${CMAKE_SOURCE_DIR}/$<TARGET_FILE_NAME:radix-test>"
  COMMENT "Copying test executable to project root")
