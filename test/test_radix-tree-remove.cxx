#include "trie.hxx"
#include <gtest/gtest.h>

/*
 * @brief Test RadixTree::remove()
 */
TEST(testradix, testremove) {
    mystuff::RadixTree test_radix{};

    test_radix.insert("");
    EXPECT_TRUE(test_radix.contains(""));
    test_radix.remove("");
    EXPECT_FALSE(test_radix.contains(""));

    test_radix.insert("Rick");
    test_radix.insert("Rodri");
    test_radix.insert("Rickos");
    test_radix.remove("AAA");
    test_radix.remove("R");
    test_radix.remove("Rick");

    EXPECT_FALSE(test_radix.contains("Rick"));
    EXPECT_TRUE(test_radix.contains("Rodri"));
    EXPECT_TRUE(test_radix.contains("Rickos"));

    test_radix.remove("Rickos");
    EXPECT_FALSE(test_radix.contains("Rickos"));
    EXPECT_TRUE(test_radix.contains("Rodri"));
}