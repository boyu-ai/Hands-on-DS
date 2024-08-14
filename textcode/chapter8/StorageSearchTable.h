#ifndef STORAGE_SEARCH_TABLE_INTERFACE_H
#define STORAGE_SEARCH_TABLE_INTERFACE_H

#include "List.h"

template <class FirstType, class SecondType>
struct Pair;

template <class KeyType, class ValueType>
class StorageSearchTable {
 public:
  virtual bool find(const KeyType &key, ValueType &value) = 0;
  virtual void insert(const KeyType &key, const ValueType &val) = 0;
  virtual void remove(const KeyType &key) = 0;
  virtual ~StorageSearchTable() {};
};

#endif  // STORAGE_SEARCH_TABLE_INTERFACE_H