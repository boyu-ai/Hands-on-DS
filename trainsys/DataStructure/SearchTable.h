#ifndef SEARCH_TABLE_H_
#define SEARCH_TABLE_H_

namespace trainsys {
    
template <class KeyType, class ValueType>
struct DataType {
    KeyType key;
    ValueType value;
    DataType(const KeyType &key_, const ValueType &value_): key(key_), value(value_) {}
};

template <class KeyType, class ValueType>
class DynamicSearchTable {
public:
    virtual DataType<KeyType, ValueType> *find(const KeyType &x) const = 0;
    virtual void insert(const DataType<KeyType, ValueType> &x) = 0;
    virtual void remove(const KeyType &x) = 0;
    virtual ~DynamicSearchTable() {};
};

template <class KeyType, class ValueType>
class StorageSearchTable {
public:
    virtual seqList<ValueType> find(const KeyType &key) = 0;
    virtual void insert(const KeyType &key, const ValueType &val) = 0;
    virtual void remove(const KeyType &key, const ValueType &val) = 0;
    virtual ~StorageSearchTable() {};
};

}

#endif