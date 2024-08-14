// 代码清单3-18至3-20 链接栈
#ifndef CHAPTER3_LINKSTACK_H
#define CHAPTER3_LINKSTACK_H
#include <iostream>

#include "stack.h"
template <class elemType>
class linkStack : public stack<elemType> {
 private:
  struct node {
    elemType data;
    node *next;
    node(const elemType &x, node *N = nullptr) {
      data = x;
      next = N;
    }
    node() : next(nullptr) {}
    ~node() {}
  };

  node *top_p;

 public:
  linkStack();
  ~linkStack();
  void push(const elemType &x);
  elemType pop();
  elemType top() const;
  bool isEmpty() const;
};

template <class elemType>
linkStack<elemType>::linkStack() {
  top_p = nullptr;
}

template <class elemType>
linkStack<elemType>::~linkStack() {
  node *tmp;
  while (top_p != nullptr) {
    tmp = top_p;
    top_p = top_p->next;
    delete tmp;
  }
}

template <class elemType>
void linkStack<elemType>::push(const elemType &x) {
  top_p = new node(x, top_p);  // 申请一个存放元素x的结点，插入单链表的表头
}

template <class elemType>
elemType linkStack<elemType>::pop() {
  node *tmp = top_p;
  elemType x = tmp->data;  // 保存栈顶元素值，以备返回
  top_p = top_p->next;  // 从单链表中删除栈顶结点
  delete tmp;           // 释放被删除的表头结点的空间
  return x;
}

template <class elemType>
elemType linkStack<elemType>::top() const {
  return top_p->data;
}

template <class elemType>
bool linkStack<elemType>::isEmpty() const {
  return top_p == nullptr;
}

#endif  // CHAPTER3_LINKSTACK_H
