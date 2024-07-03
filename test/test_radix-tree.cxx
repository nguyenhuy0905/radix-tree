#include <gtest/gtest.h>
#include "trie.hxx"

TEST(testradix, testcontains) {
    mystuff::RadixTree test_radix{};

    EXPECT_FALSE(test_radix.contains("Rick"));
    EXPECT_FALSE(test_radix.contains(""));
}

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
