// 代码清单6-1 动态查找表抽象类的定义

#ifndef CHAPTER6_DYNAMICSEARCHTABLE_H
#define CHAPTER6_DYNAMICSEARCHTABLE_H

#include "../chapter5/set.h"
template <class KEY, class OTHER>
class dynamicSearchTable {
 public:
  virtual SET<KEY, OTHER> *find(const KEY &x) const = 0;
  virtual void insert(const SET<KEY, OTHER> &x) = 0;
  virtual void remove(const KEY &x) = 0;
  virtual ~dynamicSearchTable() {};
};

#endif  // CHAPTER6_DYNAMICSEARCHTABLE_H
