// 代码清单3-2至3-7 循环队列类
#ifndef CHAPTER3_SEQQUEUE_H
#define CHAPTER3_SEQQUEUE_H

#include "queue.h"
template <class elemType>
class seqQueue : public queue<elemType> {
 private:
  elemType *elem;
  int maxSize;
  int front, rear;

  void doubleSpace();
  bool isFull() const;

 public:
  seqQueue(int size = 10);
  ~seqQueue();
  bool isEmpty() const;
  void enQueue(const elemType &x);
  elemType deQueue();
  elemType getHead() const;
};

template <class elemType>
seqQueue<elemType>::seqQueue(int size) {
  elem = new elemType[size];
  maxSize = size;
  front = rear = 0;
}

template <class elemType>
seqQueue<elemType>::~seqQueue() {
  delete[] elem;
}

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x) {
  if (isFull()) doubleSpace();
  rear = (rear + 1) % maxSize;
  elem[rear] = x;
}

template <class elemType>
elemType seqQueue<elemType>::deQueue() {
  front = (front + 1) % maxSize;
  return elem[front];
}

template <class elemType>
elemType seqQueue<elemType>::getHead() const {
  return elem[(front + 1) % maxSize];
}

template <class elemType>
bool seqQueue<elemType>::isEmpty() const {
  return front == rear;
}
template <class elemType>
bool seqQueue<elemType>::isFull() const {
  return (rear + 1) % maxSize == front;
}

template <class elemType>
void seqQueue<elemType>::doubleSpace() {
  elemType *tmp = elem;
  elem = new elemType[2 * maxSize];
  for (int i = 1; i < maxSize; ++i) {
    elem[i] = tmp[(front + i) % maxSize];
}
  front = 0;
  rear = maxSize - 1;
  maxSize *= 2;
  delete[] tmp;
}
#endif  // CHAPTER3_SEQQUEUE_H
