// #include <gtest/gtest.h>
//
// #include <memory>
// #include <string>
// #include <utility>
//
// #include "trie.hxx"
//
// struct MyRandomThing {
//   public:
//     explicit MyRandomThing(std::string str) : random(std::move(str)) {}
//     auto operator==(const MyRandomThing& other) const -> bool {
//         return this->random == other.random;
//     }
//
//   private:
//     std::string random;
// };
//
// /**
//  * @brief This is a random test, and it doesn't test the Radix tree.
//  * I was just playing around with a weak pointer and operation overloading.
//  * Pardon me, I'm new to this language.
//  */
// TEST(myrandom, testrandom) {
//     const MyRandomThing test1("aha");
//     const MyRandomThing test2("aha");
//     EXPECT_EQ(test1, test2);
//     EXPECT_TRUE(test1 == test2);
//
//     std::weak_ptr<std::string> random;
//     EXPECT_EQ(0, random.use_count());
//     random = std::make_shared<std::string>("aha");
//     EXPECT_EQ(0, random.use_count());
//     const std::shared_ptr<std::string> sstr =
//         std::make_shared<std::string>("aha");
//     random = sstr;
//     EXPECT_EQ(1, random.use_count());
// }
//
// /**
//  * @brief Test RadixTree::contains(). In this case, none of it should return
//  * true, since we have yet to add anything to the tree.
//  */
// TEST(testradix, testcontains) {
//     mystuff::RadixTree test_radix{};
//
//     EXPECT_FALSE(test_radix.contains("Rick"));
//     EXPECT_FALSE(test_radix.contains(""));
// }
//
// /**
//  * @brief Test RadixTree::insert().
//  */
// TEST(testradix, testinsert) {
//     mystuff::RadixTree test_radix{};
//
//     EXPECT_FALSE(test_radix.contains(""));
//     test_radix.insert("Rick");
//     test_radix.insert("Rodri");
//     test_radix.insert("Rickos");
//     test_radix.insert("");
//     test_radix.insert("Rick");
//     EXPECT_TRUE(test_radix.contains("Rickos"));
//     EXPECT_TRUE(test_radix.contains("Rick"));
//     EXPECT_TRUE(test_radix.contains("Rodri"));
//     EXPECT_FALSE(test_radix.contains("R"));
//     EXPECT_TRUE(test_radix.contains(""));
// }
//
// /**
//  * @brief Test RadixTree::remove()
//  */
// TEST(testradix, testremove) {
//     mystuff::RadixTree test_radix{};
//
//     test_radix.insert("");
//     EXPECT_TRUE(test_radix.contains(""));
//     test_radix.remove("");
//     EXPECT_FALSE(test_radix.contains(""));
//
//     test_radix.insert("Rick");
//     test_radix.insert("Rodri");
//     test_radix.insert("Rickos");
//     test_radix.remove("AAA");
//     test_radix.remove("R");
//     test_radix.remove("Rick");
//
//     EXPECT_FALSE(test_radix.contains("Rick"));
//     EXPECT_TRUE(test_radix.contains("Rodri"));
//     EXPECT_TRUE(test_radix.contains("Rickos"));
//
//     test_radix.remove("Rickos");
//     EXPECT_FALSE(test_radix.contains("Rickos"));
//     EXPECT_TRUE(test_radix.contains("Rodri"));
// }
