// 代码清单7-10 基数排序
//  样例输入：
//  请输入待排序数组的元素个数： 4
//  请依次输入待排序数组元素(按照key，other的形式)：
//  1 1
//  4 4
//  7 2
//  3 6
//  样例输出：
//  基数排序后的数组元素为：
//  1 1
//  3 6
//  4 4
//  7 2
#include <iostream>

#include "../chapter5/set.h"
using namespace std;

template <class OTHER>
struct node {
  SET<int, OTHER> data;
  node *next;
  node() { next = nullptr; }
  node(SET<int, OTHER> d) : data(d) { next = nullptr; }
};

template <class OTHER>
void bucketSort(node<OTHER> *&p)  // p是链接表表头
{
  // bucket, last：10个口袋
  node<OTHER> *bucket[10], *last[10], *tail;
  int i, j, k, base = 1, max = 0, len = 0;

  for (tail = p; tail != nullptr; tail = tail->next)  // 找最大键值
    if (tail->data.key > max) max = tail->data.key;

  // 寻找最大键值的位数
  if (max == 0)
    len = 0;
  else
    while (max > 0) {
      ++len;
      max /= 10;
    }

  for (i = 1; i <= len; ++i) {  // 执行len次分配和重组操作
    for (j = 0; j <= 9; ++j)
      bucket[j] = last[j] = nullptr;  // 清空口袋
    while (p != nullptr) {            // 执行一次分配
      k = p->data.key / base % 10;    // 计算结点所在的口袋
      if (bucket[k] == nullptr)
        bucket[k] = last[k] = p;
      else
        last[k] = last[k]->next = p;
      p = p->next;
    }
    p = nullptr;                // 重组后的链接表表头
    for (j = 0; j <= 9; ++j) {  // 执行重组
      if (bucket[j] == nullptr) continue;
      if (p == nullptr)
        p = bucket[j];
      else
        tail->next = bucket[j];
      tail = last[j];
    }
    tail->next = nullptr;  // 尾结点置空
    base *= 10;            // 为下一次分配做准备
  }
}

SET<int, int> a[100000];
int main() {
  cout << "请输入待排序数组的元素个数：";
  int n;
  cin >> n;
  node<int> *head;
  node<int> *tail = nullptr;
  cout << "\n请依次输入待排序数组元素(按照key，other的形式)：\n";
  int i = 0, key, other;
  do {
    cin >> key >> other;
    if (i == 0) {
      head = new node<int>(SET<int, int>(key, other));
      tail = head;
    } else {
      node<int> *currentNode =
          new node<int>(SET<int, int>(key, other));
      tail->next = currentNode;
      tail = currentNode;
    }
    i++;
  } while (i < n);
  bucketSort(head);
  cout << "\n基数排序后的数组元素为：\n";
  node<int> *currentNode = head;
  while (currentNode != nullptr) {
    cout << currentNode->data.key << ' ' << currentNode->data.other
         << endl;
    currentNode = currentNode->next;
  }
}
