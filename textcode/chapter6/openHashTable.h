// 代码清单6-18 开哈希表的定义和实现

#ifndef CHAPTER6_openHashTable_H
#define CHAPTER6_openHashTable_H
#include <iostream>

#include "dynamicSearchTable.h"
using namespace std;

template <class KEY, class OTHER>
class openHashTable : public dynamicSearchTable<KEY, OTHER> {
 private:
  struct node {  // 开哈希表中链接表的结点类
    SET<KEY, OTHER> data;
    node *next;
    node(const SET<KEY, OTHER> &d, node *n = nullptr) {
      data = d;
      next = n;
    }
    node() { next = nullptr; }
  };

  node **array;  // 指针数组
  int size;
  int (*key)(const KEY &x);
  static int defaultKey(const int &x) { return x; }

 public:
  openHashTable(int length = 101, int (*f)(const KEY &x) = defaultKey);
  ~openHashTable();
  SET<KEY, OTHER> *find(const KEY &x) const;
  void insert(const SET<KEY, OTHER> &x);
  void remove(const KEY &x);
};

template <class KEY, class OTHER>
openHashTable<KEY, OTHER>::openHashTable(int length, int (*f)(const KEY &x)) {
  size = length;
  array = new node *[size];
  key = f;
  for (int i = 0; i < size; ++i) array[i] = nullptr;
}

template <class KEY, class OTHER>
openHashTable<KEY, OTHER>::~openHashTable() {
  node *p, *q;

  for (int i = 0; i < size; ++i) {  // 释放所有单链表的空间
    p = array[i];
    while (p != nullptr) {
      q = p->next;
      delete p;
      p = q;
    };
  }

  delete[] array;
}

template <class KEY, class OTHER>
void openHashTable<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
  int pos;
  node *p;

  pos = key(x.key) % size;
  array[pos] = new node(x, array[pos]);
}

template <class KEY, class OTHER>
void openHashTable<KEY, OTHER>::remove(const KEY &x) {
  int pos;
  node *p, *q;

  pos = key(x) % size;
  if (array[pos] == nullptr) return;
  p = array[pos];
  if (array[pos]->data.key == x) {
    array[pos] = p->next;
    delete p;
    return;
  }
  while (p->next != nullptr && !(p->next->data.key == x)) p = p->next;
  if (p->next != nullptr) {
    q = p->next;
    p->next = q->next;
    delete q;
  }
}

template <class KEY, class OTHER>
SET<KEY, OTHER> *openHashTable<KEY, OTHER>::find(const KEY &x) const {
  int pos;
  node *p;

  pos = key(x) % size;
  p = array[pos];
  while (p != nullptr && !(p->data.key == x)) p = p->next;
  if (p == nullptr)
    return nullptr;
  else
    return (SET<KEY, OTHER> *)p;
}

#endif  // CHAPTER6_openHashTable_H
