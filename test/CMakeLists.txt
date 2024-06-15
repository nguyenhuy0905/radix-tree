project(radix-tree-test)

# an arbitrary list to see what the testing files are
set(test_list 
test_radix-tree-contains.cxx
test_radix-tree-insert.cxx
test_radix-tree-remove.cxx
)

# for clangd to work, I must add in stuff, manually, which is painful
set(link_libs radix-tree compiler-flags GTest::gtest_main)
add_executable(test-radix ${test_list})
target_link_libraries(test-radix ${link_libs})

enable_testing()
# include(GoogleTest)

# I need to manually add each test in for the GUI tools to recognize them.
# I hate CMake.
add_test(NAME test-radix COMMAND test-radix)