// 代码清单6-17 基于线性探测法的闭哈希表的实现

#ifndef CHAPTER6_CLOSEHASHTABLE_H
#define CHAPTER6_CLOSEHASHTABLE_H
#include <iostream>

#include "dynamicSearchTable.h"
using namespace std;

template <class KEY, class OTHER>
class closeHashTable : public dynamicSearchTable<KEY, OTHER> {
 private:
  struct node {  // 哈希表的结点类
    SET<KEY, OTHER> data;
    int state;  // 0：结点为空   1：结点已用   2：结点已被删除
    node() { state = 0; }
  };

  node *array;
  int size;
  int (*key)(const KEY &x);
  static int defaultKey(const int &x) { return x; }

 public:
  closeHashTable(int length = 101, int (*f)(const KEY &x) = defaultKey);
  ~closeHashTable() { delete[] array; }
  SET<KEY, OTHER> *find(const KEY &x) const;
  void insert(const SET<KEY, OTHER> &x);
  void remove(const KEY &x);
};

template <class KEY, class OTHER>
closeHashTable<KEY, OTHER>::closeHashTable(
    int length, int (*f)(const KEY &x)) {
  size = length;
  array = new node[size];
  key = f;
}

template <class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
  int initPos, pos;

  initPos = pos = key(x.key) % size;
  do {
    if (array[pos].state != 1) {  // 找到空位置
      array[pos].data = x;
      array[pos].state = 1;
      return;
    }
    pos = (pos + 1) % size;
  } while (pos != initPos);
}

template <class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::remove(const KEY &x) {
  int initPos, pos;
  initPos = pos = key(x) % size;
  do {
    if (array[pos].state == 0) return;
    if (array[pos].state == 1 &&
        array[pos].data.key == x) {  // 找到键值为x的数据元素，删除
      array[pos].state = 2;
      return;
    }
    pos = (pos + 1) % size;
  } while (pos != initPos);
}

template <class KEY, class OTHER>
SET<KEY, OTHER> *closeHashTable<KEY, OTHER>::find(const KEY &x) const {
  int initPos, pos;
  initPos = pos = key(x) % size;
  do {
    if (array[pos].state == 0) return nullptr;  // 没有找到
    if (array[pos].state == 1 && array[pos].data.key == x)  // 找到
      return (SET<KEY, OTHER> *)&array[pos];
    pos = (pos + 1) % size;
  } while (pos != initPos);
}

#endif  // CHAPTER6_CLOSEHASHTABLE_H
