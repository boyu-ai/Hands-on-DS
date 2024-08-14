#ifndef CACHED_BPLUS_TREE_H_
#define CACHED_BPLUS_TREE_H_

#include "SearchTable.h"
#include "BPlusTree.h"
#include "RedBlackTree.h"

namespace trainsys {

template <class KeyType, class ValueType>
class CachedBPlusTree {
private:
    // 缓存策略：write through
    BPlusTree<KeyType, ValueType> storage;
    RedBlackTree<KeyType, ValueType> cache;
    
public:
    CachedBPlusTree(const char* filename): storage(filename), cache() {}
    ~CachedBPlusTree() = default;

    bool contains(const KeyType &x) {
        if (cache.find(x) != nullptr) return true;
        return storage.contains(x);
    }

    ValueType find(const KeyType &x) {
        if (cache.find(x) != nullptr) return cache.find(x)->value;
        return storage.findFirst(x);
    }
    void insert(const KeyType &key, const ValueType &value) {
        storage.insert(key, value);
        cache.insert(DataType<KeyType, ValueType>(key, value));
    }
    void remove(const KeyType &x) {
        storage.removeFirst(x);
        cache.remove(x);
    }
};

} // namespace trainsys

#endif 