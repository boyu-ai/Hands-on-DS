#ifndef LIST_H_
#define LIST_H_

#include <iostream>

namespace trainsys {

template <class elemType>
class list {
   public:
    virtual void clear() = 0;
    virtual int length() const = 0;
    virtual void insert(int i, const elemType &x) = 0;
    virtual void remove(int i) = 0;
    // virtual int search(const elemType &x) const = 0;
    virtual elemType visit(int i) const = 0;
    // virtual void traverse() const = 0;
    virtual ~list() {};
};

template <class elemType>
class seqList: public list<elemType> {
protected:
    elemType *data;
    int currentLength;
    int maxSize;
    void doubleSpace();

public:
    seqList(int initSize = 10);
    ~seqList() { delete[] data; }
    void clear() { currentLength = 0; }
    int length() const { return currentLength; }
    bool empty() const { return currentLength == 0; }
    void insert(int i, const elemType &x);
    void pushBack(const elemType &x);
    void popBack();
    void remove(int i);
    // int search(const elemType &x) const;
    elemType back() const;
    elemType visit(int i) const { return data[i]; }
    // void traverse() const;
};

template <class elemType>
seqList<elemType>::seqList(int initSize) {
    data = new elemType[initSize];
    maxSize = initSize;
    currentLength = 0;
}

// template <class elemType>
// int seqList<elemType>::search(const elemType &x) const {
//     int i;
//     for (i = 0; i < currentLength && data[i] != x; ++i);
//     if (i == currentLength) return -1;
//     else return i;
// }

// template <class elemType>
// void seqList<elemType>::traverse() const {
//     for (int i = 0; i < currentLength; ++i) std::cout << data[i] << ' ';
//     std::cout << std::endl;
// }

template <class elemType>
void seqList<elemType>::insert(int i, const elemType &x) {
    if (currentLength == maxSize)  // 如果当前表长已经达到了申请空间的上限
        doubleSpace();             // 就必须执行扩大数组空间的操作
    for (int j = currentLength; j > i; j--)
        data[j] = data[j - 1];  // 将第 i 个元素到最后一个元素的储存位置全部后移一个位置
    data[i] = x;                // 第 i 个位置就空了出来，可以插入
    ++currentLength;
}

template <class elemType>
void seqList<elemType>::pushBack(const elemType &x) {
    insert(length(), x);
}

template <class elemType>
void seqList<elemType>::popBack() {
    remove(length() - 1);
}

template <class elemType>
void seqList<elemType>::doubleSpace() {
    elemType *tmp = data;
    maxSize *= 2;
    data = new elemType[maxSize];                              // 申请容量翻倍的新空间
    for (int i = 0; i < currentLength; ++i) data[i] = tmp[i];  // 将数据从旧空间搬运到新空间里
    delete[] tmp;                                              // 回收旧空间
}

template <class elemType>
void seqList<elemType>::remove(int i) {
    for (int j = i; j < currentLength - 1; j++)
        data[j] = data[j + 1];  // 将第 i+1 个元素到最后一个元素的储存位置全部前移一个位置
    --currentLength;
}

template <class elemType>
elemType seqList<elemType>::back() const {
    return visit(length() - 1);
}

}

#endif 