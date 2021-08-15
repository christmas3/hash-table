#include <gtest/gtest.h>

#include "HashTable.h"

TEST(HashTable, HashTableTest)
{
    container::HashTable<std::string, int> hashTable;

    EXPECT_EQ(hashTable.capacity(), container::kDefaultCapacity);
    EXPECT_EQ(hashTable.size(), 0);
    EXPECT_TRUE(hashTable.empty());
    EXPECT_EQ(hashTable.threshold(), 7);

    EXPECT_FALSE(hashTable.insert({ "hello", 1 }).second);
    EXPECT_EQ(hashTable.size(), 1);
    EXPECT_FALSE(hashTable.empty());
}
