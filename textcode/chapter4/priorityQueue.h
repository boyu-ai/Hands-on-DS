// 代码清单4-12至4-17 优先级队列类的定义和实现
#ifndef CHAPTER4_PRIORITYQUEUE_H
#define CHAPTER4_PRIORITYQUEUE_H

#include "../chapter3/queue.h"

template <class elemType>
class priorityQueue : public queue<elemType> {
 private:
  int currentSize;  // 队列长度
  elemType *array;  // 指向数组起始地址的指针
  int maxSize;      // 容量

 public:
  priorityQueue(int capacity = 100);
  priorityQueue(const elemType data[], int size);
  ~priorityQueue();
  void enQueue(const elemType &x);
  elemType deQueue();
  elemType getHead() const;
  bool isEmpty() const;

 private:
  void doubleSpace();
  void buildHeap();
  void percolateDown(int hole);
};

template <class elemType>
priorityQueue<elemType>::priorityQueue(int capacity) {
  array = new elemType[capacity];
  maxSize = capacity;
  currentSize = 0;
}

template <class elemType>
priorityQueue<elemType>::~priorityQueue() {
  delete[] array;
}

template <class elemType>
elemType priorityQueue<elemType>::getHead() const {
  return array[1];
}

template <class elemType>
bool priorityQueue<elemType>::isEmpty() const {
  return currentSize == 0;
}

template <class elemType>
void priorityQueue<elemType>::doubleSpace() {
  elemType *tmp = array;

  maxSize *= 2;
  array = new elemType[maxSize];
  for (int i = 0; i <= currentSize; ++i) array[i] = tmp[i];
  delete[] tmp;
}
template <class elemType>
void priorityQueue<elemType>::enQueue(const elemType &x) {
  if (currentSize == maxSize - 1) doubleSpace();

  // 向上过滤
  int hole = ++currentSize;
  for (; hole > 1 && x < array[hole / 2]; hole /= 2)
    array[hole] = array[hole / 2];
  array[hole] = x;
}

template <class elemType>
elemType priorityQueue<elemType>::deQueue() {
  elemType minItem;
  minItem = array[1];  // 根结点保存的是二叉堆的最小值
  array[1] = array[currentSize--];  // 将二叉堆最后一个数据元素移到根结点
  percolateDown(1);                 // 将根结点的数据元素向下过滤
  return minItem;
}

template <class elemType>
void priorityQueue<elemType>::percolateDown(int hole) {
  int child;
  // 将待过滤结点的值保存在tmp中
  elemType tmp = array[hole];

  // 向下过滤
  // hole中保存空结点的位置
  for (; hole * 2 <= currentSize; hole = child) {
    child = hole * 2;  // 找到结点的左儿子
    if (child != currentSize && array[child + 1] < array[child])
      child++;  // child变量保存左、右子结点中值较小的子结点
    // 如果tmp比child大，那么由child代替空结点，空结点则向下过滤了一层
    if (array[child] < tmp)
      array[hole] = array[child];
    else
      break;  // 当前的空结点是一个符合规定的位置，向下过滤结束
  }
  array[hole] = tmp;  // 将待过滤结点的值写入空结点
}

template <class elemType>
void priorityQueue<elemType>::buildHeap() {
  for (int i = currentSize / 2; i > 0; i--) percolateDown(i);
}
template <class elemType>
priorityQueue<elemType>::priorityQueue(const elemType *items, int size)
    : maxSize(size + 10), currentSize(size) {
  array = new elemType[maxSize];
  for (int i = 0; i < size; i++) array[i + 1] = items[i];
  buildHeap();
}

#endif  // CHAPTER4_PRIORITYQUEUE_H
