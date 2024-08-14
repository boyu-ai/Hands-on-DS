// 代码清单3-8至3-9 链接队列类
#ifndef CHAPTER3_LINKQUEUE_H
#define CHAPTER3_LINKQUEUE_H

#include <iostream>

#include "queue.h"
template <class elemType>
class linkQueue : public queue<elemType> {
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

  node *front, *rear;

 public:
  linkQueue();
  ~linkQueue();
  bool isEmpty() const;
  void enQueue(const elemType &x);
  elemType deQueue();
  elemType getHead() const;
};

template <class elemType>
linkQueue<elemType>::linkQueue() {
  front = rear = nullptr;
}

template <class elemType>
linkQueue<elemType>::~linkQueue() {
  node *tmp;
  while (front != nullptr) {
    tmp = front;
    front = front->next;
    delete tmp;
  }
}

template <class elemType>
bool linkQueue<elemType>::isEmpty() const {
  return front == nullptr;
}

template <class elemType>
elemType linkQueue<elemType>::getHead() const {
  return front->data;
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x) {
  if (rear == nullptr)  // 入队前为空队列
    front = rear = new node(x);
  else
    rear = rear->next = new node(x);
}

template <class elemType>
elemType linkQueue<elemType>::deQueue() {
  node *tmp = front;
  elemType value = front->data;
  front = front->next;
  if (front == nullptr) rear = nullptr;  // 出队后为空队列
  delete tmp;
  return value;
}

#endif  // CHAPTER3_LINKQUEUE_H
