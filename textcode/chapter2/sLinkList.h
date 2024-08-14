// 代码清单2-6至2-8 单链表类的定义和实现
#ifndef CHAPTER2_SLINKLIST_H
#define CHAPTER2_SLINKLIST_H

#include <iostream>

#include "list.h"
using namespace std;

template <class elemType>
class sLinkList : public list<elemType> {
 private:
  struct node {
    elemType data;
    node *next;
    node(const elemType &x, node *n = nullptr) {
      data = x;
      next = n;
    }
    node() : next(nullptr) {}
    ~node() {};
  };

  node *head;
  int currentLength;
  node *find(int i) const;

 public:
  sLinkList() {
    head = new node;  // 申请头结点
    currentLength = 0;
  }
  ~sLinkList() {
    clear();
    delete head;  // 删除头结点
  }
  void clear();
  int length() const { return currentLength; }
  void insert(int i, const elemType &x);
  void remove(int i);
  int search(const elemType &x) const;
  elemType visit(int i) const;
  void traverse() const;
};

template <class elemType>
void sLinkList<elemType>::insert(int i, const elemType &x) {
  node *pos;
  pos = find(i - 1);  // 找到指向第i−1个结点的指针
  // 将第i−1个结点的后继指针指向新结点，新结点指向原来的第i个结点
  pos->next = new node(x, pos->next);
  ++currentLength;
}

template <class elemType>
void sLinkList<elemType>::remove(int i) {
  node *pos, *delp;
  pos = find(i - 1);  // 找到前一个结点的地址
  delp = pos->next;   // 找到要删除的结点
  pos->next = delp->next;  // 把前一个结点的指针指向delp的后一个结点
  delete delp;
  --currentLength;
}

// 按序删除头结点以外的所有真的包含元素的结点
template <class elemType>
void sLinkList<elemType>::clear() {
  node *p = head->next, *q;
  head->next = nullptr;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  currentLength = 0;
}

// 返回第i个结点的地址
template <class elemType>
typename sLinkList<elemType>::node *sLinkList<elemType>::find(
    int i) const {
  node *p = head;
  while (i-- >= 0) p = p->next;
  return p;
}

template <class elemType>
int sLinkList<elemType>::search(const elemType &x) const {
  node *p = head->next;
  int i = 0;
  while (p != nullptr && p->data != x) {
    p = p->next;
    ++i;
  }
  if (p == nullptr)
    return -1;
  else
    return i;
}

template <class elemType>
elemType sLinkList<elemType>::visit(int i) const {
  return find(i)->data;  // 找到第i个结点的地址，访问其中的data
}

template <class elemType>
void sLinkList<elemType>::traverse() const {
  node *p = head->next;
  while (p != nullptr) {
    cout << p->data << "  ";
    p = p->next;
  }
  cout << endl;
}

#endif  // CHAPTER2_SLINKLIST_H
