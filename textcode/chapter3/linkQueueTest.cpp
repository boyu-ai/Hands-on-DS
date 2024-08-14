// 链接队列类的测试程序
// 入队： enqueue
// 出队： dequeue
// 获取头元素：gethead
// 样例输入：
// enqueue 1
// enqueue 2
// enqueue 3
// dequeue
// gethead
// dequeue
// dequeue
// 样例输出：
// Dequeue element 1
// Head element is 2
// Dequeue element 2
// Dequeue element 3

#include <cassert>
#include <cstring>
#include <iostream>

#include "linkQueue.h"

using namespace std;
int main() {
  linkQueue<int> *link_queue = new linkQueue<int>();
  assert(link_queue->isEmpty());  // 检查isEmpty函数
  while (true) {
    char op[10];
    cin >> op;
    if (strcmp(op, "enqueue") == 0) {
      int x;
      cin >> x;
      link_queue->enQueue(x);
    } else if (strcmp(op, "dequeue") == 0) {
      cout << "Dequeue element " << link_queue->deQueue() << endl;
    } else if (strcmp(op, "gethead") == 0) {
      cout << "Head element is " << link_queue->getHead() << endl;
    } else if (strcmp(op, "exit") == 0) {
      return 0;
    } else
      cout << "Invalid operation!" << endl;
  }
}