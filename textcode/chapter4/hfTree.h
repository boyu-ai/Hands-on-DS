// 代码清单4-9至4-10 哈夫曼树的实现
#ifndef CHAPTER4_HFTREE_H
#define CHAPTER4_HFTREE_H
#include <iomanip>
#include <iostream>
using namespace std;

template <class elemType>
class hfTree {
 private:
  struct Node  // 数组中的元素类型
  {
    elemType data;            // 结点值
    int weight;               // 结点的权值
    int parent, left, right;  // 父结点及左\右儿子的下标
  };

  Node *elem;
  int length;

 public:
  struct hfCode {   // 哈夫曼编码的类型
    elemType data;  // 待编码的字符
    string code;    // 对应的哈夫曼编码
  };

  hfTree(const elemType *x, const int *w, int size);
  void getCode(hfCode result[]);  // 由哈夫曼树生成哈夫曼编码
  ~hfTree() { delete[] elem; }
};

template <class elemType>
hfTree<elemType>::hfTree(const elemType *v, const int *w, int size) {
  const int MAX_INT = 32767;
  int min1, min2;            // 最小树、次最小树的权值
  int minIndex1, minIndex2;  // 最小树、次最小树的下标

  // 置初值
  length = 2 * size;
  elem = new Node[length];
  for (int i = size; i < length; ++i) {
    elem[i].weight = w[i - size];
    elem[i].data = v[i - size];
    elem[i].parent = elem[i].left = elem[i].right = 0;
  }
  // 归并森林中的树
  for (int i = size - 1; i > 0; --i) {
    min1 = min2 = MAX_INT;
    minIndex1 = minIndex2 = 0;
    for (int j = i + 1; j < length; ++j)
      if (elem[j].parent == 0)
        if (elem[j].weight < min1) {  // 元素j最小
          min2 = min1;
          min1 = elem[j].weight;
          minIndex1 = minIndex2;
          minIndex2 = j;
        } else if (elem[j].weight < min2) {  // 元素j次小
          min2 = elem[j].weight;
          minIndex1 = j;
        }
    elem[i].weight = min1 + min2;
    elem[i].left = minIndex1;
    elem[i].right = minIndex2;
    elem[i].parent = 0;
    elem[minIndex1].parent = i;
    elem[minIndex2].parent = i;
  }
}

template <class elemType>
void hfTree<elemType>::getCode(hfCode result[]) {
  int size = length / 2;
  int p, s;  // s是追溯过程中正在处理的结点，p是s的父结点下标

  for (int i = size; i < length; ++i) {  // 遍历每个待编码的字符
    result[i - size].data = elem[i].data;
    result[i - size].code = "";
    p = elem[i].parent;
    s = i;
    while (p) {  // 向根追溯
      if (elem[p].left == s)
        result[i - size].code = '0' + result[i - size].code;
      else
        result[i - size].code = '1' + result[i - size].code;
      s = p;
      p = elem[p].parent;
    }
  }
}

#endif  // CHAPTER4_HFTREE_H
