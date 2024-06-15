#include "trie.hxx"
#include <gtest/gtest.h>
/**
 * @brief Test RadixTree::insert().
 */
TEST(testradix, testinsert) {
    mystuff::RadixTree test_radix{};

    EXPECT_FALSE(test_radix.contains(""));
    test_radix.insert("Rick");
    test_radix.insert("Rodri");
    test_radix.insert("Rickos");
    test_radix.insert("");
    test_radix.insert("Rick");
    EXPECT_TRUE(test_radix.contains("Rickos"));
    EXPECT_TRUE(test_radix.contains("Rick"));
    EXPECT_TRUE(test_radix.contains("Rodri"));
    EXPECT_FALSE(test_radix.contains("R"));
    EXPECT_TRUE(test_radix.contains(""));
}