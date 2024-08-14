#ifndef LIST_H_
#define LIST_H_

#include <iostream>
using namespace std;

namespace trainsys {

template <class elemType>
class list {
 public:
  virtual void clear() = 0;
  virtual int length() const = 0;
  virtual void insert(int i, const elemType &x) = 0;
  virtual void remove(int i) = 0;
  virtual int search(const elemType &x) const = 0;
  virtual elemType visit(int i) const = 0;
  virtual void traverse() const = 0;
  virtual ~list() {};
};

template <class elemType>
class seqList : public list<elemType> {
 private:
  elemType *data;
  int currentLength;
  int maxSize;
  void doubleSpace();

 public:
  seqList(int initSize = 10);
  ~seqList() { delete[] data; }  // 释放动态数组的空间
  void clear() { currentLength = 0; }
  int length() const { return currentLength; }
  void insert(int i, const elemType &x);
  void remove(int i);
  int search(const elemType &x) const;
  elemType visit(int i) const { return data[i]; }
  void traverse() const;
};

template <class elemType>
seqList<elemType>::seqList(int initSize) {
  data = new elemType[initSize];
  maxSize = initSize;
  currentLength = 0;
}

template <class elemType>
int seqList<elemType>::search(const elemType &x) const {
  int i;
// 使用for循环逐位搜索data[i]是否等于x
  for (i = 0; i < currentLength && data[i] != x; ++i);
  if (i == currentLength)
    return -1;
  else
    return i;
}

template <class elemType>
void seqList<elemType>::traverse() const {
  for (int i = 0; i < currentLength; ++i) cout << data[i] << ' ';
  cout << endl;
}

// 在第i个位置插入元素x
template <class elemType>
void seqList<elemType>::insert(int i, const elemType &x) {
  // 如果当前表长已经达到了申请空间的上限，则必须执行扩大数组空间的操作
  if (currentLength == maxSize) doubleSpace();

  // 将第 i 个元素到最后一个元素的储存位置全部后移一个位置
  for (int j = currentLength; j > i; j--) data[j] = data[j - 1];
  data[i] = x;
  ++currentLength;
}

// 自动扩容函数doubleSpace()
template <class elemType>
void seqList<elemType>::doubleSpace() {
  elemType *tmp = data;
  maxSize *= 2;
  data = new elemType[maxSize];  // 申请容量翻倍的新空间
  for (int i = 0; i < currentLength; ++i)
    data[i] = tmp[i];  // 将数据从旧空间复制到新空间
  delete[] tmp;        // 回收旧空间
}

// 删除第i个位置的元素
template <class elemType>
void seqList<elemType>::remove(int i) {
  // 将第i+1个元素到最后一个元素全部前移一个位置
  for (int j = i; j < currentLength - 1; j++) data[j] = data[j + 1];
  --currentLength;
}

}  // namespace trainsys

#endif