add_library(radix-tree STATIC trie.cxx)
target_link_libraries(radix-tree compiler-flags)
target_include_directories(radix-tree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
