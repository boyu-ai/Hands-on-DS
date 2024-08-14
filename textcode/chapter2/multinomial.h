// 代码清单2-14 多项式单链表的结点类Node的定义和功能函数add()的实现
#ifndef CHAPTER2_MULTINOMIAL_H
#define CHAPTER2_MULTINOMIAL_H
#include <iostream>
using namespace std;

class Node {  // 多项式单链表的结点类定义
 public:
  int coff, exp;  // coff保存系数，exp保存指数
  Node *next;
  Node() { next = nullptr; }
  Node(int n1, int n2, Node *p = nullptr) : coff(n1), exp(n2), next(p) {}
};
Node *add(Node *exp1, Node *exp2) {
  Node *res, *p, *tmp;
  // res是保存加的结果值的单链表，p指向res的表尾结点
  res = p = new Node();  // 为存储结果值的单链表申请头结点
  exp1 = exp1->next;
  exp2 = exp2->next;
  while (exp1 != nullptr && exp2 != nullptr) {  // 归并两个单链表
    if (exp1->exp < exp2->exp) {                // 直接复制表达式1的项
      p = p->next = new Node(exp1->coff, exp1->exp);
      exp1 = exp1->next;
    } else if (exp1->exp > exp2->exp) {  // 直接复制表达式2的项
      p = p->next = new Node(exp2->coff, exp2->exp);
      exp2 = exp2->next;
    } else if (exp1->coff + exp2->coff != 0) {
      // 归并两个表达式的同次项
      p = p->next = new Node(exp1->coff + exp2->coff, exp2->exp);
      exp1 = exp1->next;
      exp2 = exp2->next;
    }
  }
  // 将遍历尚未结束的表达式并入结果表达式
  if (exp1 == nullptr)
    tmp = exp2;
  else
    tmp = exp1;
  while (tmp != nullptr) {
    p->next = new Node(tmp->coff, tmp->exp);
    tmp = tmp->next;
    p = p->next;
  }
  return res;
}
#endif  // CHAPTER2_MULTINOMIAL_H
