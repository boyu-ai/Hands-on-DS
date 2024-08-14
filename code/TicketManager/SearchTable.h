#ifndef SEARCH_TABLE_H_
#define SEARCH_TABLE_H_

namespace trainsys {

template <class KeyType, class ValueType>
class StorageSearchTable {
 public:
  virtual seqList<ValueType> find(const KeyType &key) = 0;
  virtual void insert(const KeyType &key, const ValueType &val) = 0;
  virtual void remove(const KeyType &key, const ValueType &val) = 0;
  virtual ~StorageSearchTable() {};
};

}  // namespace trainsys

#endif