project(radix-tree-test)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG f8d7d77)

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(test-tree test_radix-tree.cxx)
target_link_libraries(test-tree PRIVATE compiler-flags GTest::gtest_main
                                        radix-tree)

gtest_discover_tests(test-tree)
