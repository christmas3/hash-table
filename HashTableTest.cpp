#include <gtest/gtest.h>

#include "HashTable.h"

#include <string>

TEST(HashTable, HashTableInsertTest)
{
    container::HashTable<std::string, int> hashTable;

    EXPECT_EQ(hashTable.capacity(), container::kDefaultCapacity);
    EXPECT_EQ(hashTable.size(), 0);
    EXPECT_TRUE(hashTable.empty());
    EXPECT_EQ(hashTable.threshold(), 7);

    EXPECT_FALSE(hashTable.insert({ "hello", 1 }).second);
    EXPECT_EQ(hashTable.size(), 1);
    EXPECT_FALSE(hashTable.empty());

    auto findRes = hashTable.find("hello");
    EXPECT_TRUE(findRes != nullptr);
    EXPECT_EQ(findRes->second, 1);

    EXPECT_TRUE(hashTable.find("cat") == nullptr);

    auto prevVal = hashTable.insert({ "hello", 12 });
    EXPECT_TRUE(prevVal.second);
    EXPECT_EQ(hashTable.size(), 1);
    EXPECT_EQ(prevVal.first, 1);

    findRes = hashTable.find("hello");
    EXPECT_TRUE(findRes != nullptr);
    EXPECT_EQ(findRes->second, 12);
}

TEST(HashTable, HashTableRehashTest)
{
    container::HashTable<std::string, int> hashTable;
    EXPECT_EQ(hashTable.size(), 0);
    EXPECT_TRUE(hashTable.empty());

    auto capacity = hashTable.capacity();
    auto threshold = hashTable.threshold();

    std::string key = "some key N";
    for (size_t i = 0; i <= threshold; ++i) {
        key.back() = 30 + i;
        hashTable.insert({ key, i });
    }

    EXPECT_EQ(hashTable.size(), threshold + 1);
    EXPECT_FALSE(hashTable.empty());
    EXPECT_EQ(hashTable.capacity(), capacity * 2 + 1);
    EXPECT_EQ(hashTable.threshold(), static_cast<int>(hashTable.capacity() * hashTable.loadFactor()));

    for (auto val : { 7, 4, 0 }) {
        key.back() = 30 + val;
        auto findRes = hashTable.find(key);
        EXPECT_TRUE(findRes != nullptr);
        EXPECT_EQ(findRes->second, val);
    }
}

TEST(HashTable, HashTableRemoveTest)
{
    container::HashTable<std::string, int> hashTable;
    EXPECT_EQ(hashTable.size(), 0);
    EXPECT_TRUE(hashTable.empty());

    auto threshold = hashTable.threshold();

    std::string key = "some key N";
    for (size_t i = 0; i <= threshold; ++i) {
        key.back() = 30 + i;
        hashTable.insert({ key, i });
    }

    EXPECT_EQ(hashTable.size(), threshold + 1);
    EXPECT_FALSE(hashTable.empty());

    auto result = hashTable.remove("some key");
    EXPECT_FALSE(result.second);

    for (size_t i = 0; i <= threshold; ++i) {
        key.back() = 30 + i;
        result = hashTable.remove(key);
        EXPECT_TRUE(result.second);
        EXPECT_EQ(result.first, i);
        EXPECT_EQ(hashTable.size(), threshold - i);
    }

    EXPECT_EQ(hashTable.size(), 0);
    EXPECT_TRUE(hashTable.empty());
}
