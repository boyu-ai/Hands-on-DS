// multinomial类的测试程序
// 按样例格式输入两个多项式表达式（expression1）（expression2)，输出两个多项式的和
// 输入样例：
// 1 0    （第一个数字是多项式的系数，第二个数字为多项式的指数，按照指数从小到大依次输入）
// 2 2
// 0 -1   （系数为-1表示多项式结束）
// 1 2
// 2 3
// 0 -1   （系数为-1表示多项式结束）
// 输出样例：+1x^0+3x^2+2x^3

#include <cassert>
#include <cstdio>
#include <iostream>

#include "multinomial.h"
using namespace std;

void print_poly(Node *head) {
  Node *node = head->next;
  while (node != nullptr) {
    if (node->coff > 0) {
      cout << '+' << node->coff << "x^" << node->exp;
    } else if (node->coff < 0) {
      cout << node->coff << "x^" << node->exp;
    }
    node = node->next;
  }
}

int main() {
  Node *exp_linked_list1 = new Node;
  Node *current_node = exp_linked_list1;
  int coff, exp = 0;
  while (1) {
    cin >> coff >> exp;
    if (exp == -1) break;
    Node *new_node = new Node(coff, exp);
    current_node->next = new_node;
    current_node = new_node;
  }
  Node *exp_linked_list2 = new Node;
  current_node = exp_linked_list2;
  coff = 0, exp = 0;
  while (1) {
    cin >> coff >> exp;
    if (exp == -1) break;
    Node *new_node = new Node(coff, exp);
    current_node->next = new_node;
    current_node = new_node;
  }
  Node *sum = add(exp_linked_list1, exp_linked_list2);
  print_poly(sum);
  return 0;
}