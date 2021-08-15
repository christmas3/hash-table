#pragma once

#include <utility>

namespace container {
const std::size_t kDefaultCapacity = 11;
const float kDefaultLoadFactor = 0.7;

template<typename K, typename V>
class HashTable
{
public:
    using KeyType = K;
    using ValueType = std::pair<K, V>;
    using Iterator = ValueType*;
    using SizeType = std::size_t;

    explicit HashTable(SizeType capacity = kDefaultCapacity)
        : capacity_(capacity)
        , buckets_(new ForwardList[capacity_])
        , loadFactor_(kDefaultLoadFactor)
        , threshold_(capacity_ * loadFactor_)
        , size_(0)
    {
    }

    ~HashTable() { delete[] buckets_; }

    [[nodiscard]] SizeType capacity() const { return capacity_; }
    [[nodiscard]] SizeType threshold() const { return threshold_; }
    [[nodiscard]] SizeType size() const { return size_; }
    [[nodiscard]] bool empty() const { return size_ == 0; }

    std::pair<V, bool> insert(const ValueType& val) { insert(std::move(ValueType(val))); }
    std::pair<V, bool> insert(ValueType&& val)
    {
        std::pair<V, bool> result;
        auto idx = hash(val.first);
        auto* e = buckets_[idx].begin();
        while (e) {
            if (e->val.first == val.first) {
                result.first = std::move(e->val.second);
                result.second = true;
                e->val = std::move(val);
                return result;
            }
            else {
                e = e->next;
            }
        }
        if (++size_ > threshold_) {
            rehash();
            idx = hash(val.first);
        }
        buckets_[idx].addFront(std::move(val));
        result.second = false;
        return result;
    }

    void rehash()
    {
        auto* oldBuckets = buckets_;
        auto oldCapacity = capacity_;
        capacity_ = capacity_ * 2 + 1;
        threshold_ = capacity_ * loadFactor_;
        buckets_ = new ForwardList[capacity_];
        for (int i = 0; i < oldCapacity; ++i) {
            auto e = oldBuckets[i].begin();
            while (e) {
                auto idx = hash(e->val.first);
                buckets_[idx].addBack(e);
                auto next = e->next;
                e->next = nullptr;
                e = next;
            }
        }

        delete[] oldBuckets;
    }

private:
    std::size_t hash(const KeyType& key) const
    {
        auto h = std::hash<KeyType>{}(key) % capacity_;
        return h < 0 ? -h : h;
    }

    struct ForwardList
    {
        struct Node
        {
            ValueType val;
            Node* next;
        };

        void addFront(const ValueType& val) { begin_ = new Node{ val, begin_ }; }
        void addFront(ValueType&& val) { begin_ = new Node{ std::move(val), begin_ }; }

        void addBack(Node* n)
        {
            auto* prev = begin_;
            if (prev) {
                auto* next = prev->next;
                while (next) {
                    prev = next;
                    next = prev->next;
                }
            }
            prev->next = n;
        }

        Node* begin() { return begin_; }

        ForwardList()
            : begin_(nullptr)
        {
        }
        ~ForwardList()
        {
            while (begin_) {
                auto next = begin_->next;
                delete begin_;
                begin_ = next;
            }
        }

    private:
        Node* begin_;
    };

    SizeType capacity_;
    ForwardList* buckets_;
    float loadFactor_;
    SizeType threshold_;
    SizeType size_;
};

} // namespace container
