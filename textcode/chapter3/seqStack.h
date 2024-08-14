// 代码清单3-12至代码清单3-17 顺序栈

#ifndef CHAPTER3_SEQSTACK_H
#define CHAPTER3_SEQSTACK_H
#include "stack.h"
template <class elemType>
class seqStack : public stack<elemType> {
 private:
  elemType *elem;      // 栈的存储空间，即动态数组
  int maxSize;         // 数组规模
  int top_p;           // 保存栈顶位置
  void doubleSpace();  // 用于扩展数组空间的私有工具函数

 public:
  // 函数继承于stack基类
  seqStack(int initSize = 10);
  ~seqStack();

  void push(const elemType &x);
  elemType pop();
  elemType top() const;
  bool isEmpty() const;
};
template <class elemType>
seqStack<elemType>::seqStack(int initSize) {
  elem = new elemType[initSize];
  maxSize = initSize;
  top_p = -1;
}

template <class elemType>
seqStack<elemType>::~seqStack() {
  delete[] elem;
}
template <class elemType>
void seqStack<elemType>::doubleSpace() {
  elemType *tmp = elem;  // 创建空间是原数组两倍的新数组
  elem = new elemType[2 * maxSize];
  // 将原数组的数据移动到新数组中
  for (int i = 0; i < maxSize; ++i) elem[i] = tmp[i];
  maxSize *= 2;
  delete[] tmp;  // 将旧的数组空间销毁
}
template <class elemType>
void seqStack<elemType>::push(const elemType &x) {
  if (top_p == maxSize - 1) doubleSpace();
  elem[++top_p] = x;
}
template <class elemType>
elemType seqStack<elemType>::pop() {
  return elem[top_p--];
}

template <class elemType>
elemType seqStack<elemType>::top() const {
  return elem[top_p];
}
template <class elemType>
bool seqStack<elemType>::isEmpty() const {
  return top_p == -1;
}
#endif  // CHAPTER3_SEQSTACK_H
