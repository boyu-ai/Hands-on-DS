// 顺序栈的测试程序
// 入栈：push
// 出栈并获取栈顶元素：pop
// 获取栈顶元素：top
// 退出：exit
// 样例输入：
// push 1
// push 2
// top
// push 3
// pop
// pop
// pop
// exit
// 样例输出：
// Top element is 2
// Pop element 3
// Pop element 2
// Pop element 1
#include <cassert>
#include <cstring>
#include <iostream>

#include "seqStack.h"

using namespace std;
int main() {
  seqStack<int> *seq_stack = new seqStack<int>();
  assert(seq_stack->isEmpty());  // 检查isEmpty函数
  while (true) {
    char op[10];
    cin >> op;
    if (strcmp(op, "push") == 0) {
      int x;
      cin >> x;
      seq_stack->push(x);
    } else if (strcmp(op, "pop") == 0) {
      cout << "Pop element " << seq_stack->pop() << endl;
    } else if (strcmp(op, "top") == 0) {
      cout << "Top element is " << seq_stack->top() << endl;
    } else if (strcmp(op, "exit") == 0) {
      return 0;
    } else
      cout << "Invalid operation!" << endl;
  }
}