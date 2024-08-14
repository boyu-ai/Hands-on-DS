// 优先级队列测试程序
// 首先，初始化优先级队列。
// 样例：
// 初始化优先级队列，请输入元素个数：5
// 请输入初始化的元素：1 4 2 3 6
// 优先级队列初始化已完成！
// 接下来，可以输入enqueue，dequeue和getHead，执行入队、出队、获取队列头
// 输入：dequeue 输出：Dequeue element 1
// 输入：enqueue 5
// 输入：getHead 输出：Head element is 2
// 输入：dequeue 输出：Dequeue element 2
// 输入：dequeue 输出：Dequeue element 3
// 输入：dequeue 输出：Dequeue element 4
// 输入：dequeue 输出：Dequeue element 5
// 输入：dequeue 输出：Dequeue element 6
// 输入：exit

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>

#include "priorityQueue.h"
using namespace std;

int main() {
  cout << "初始化优先级队列，请输入元素个数：";
  int n;
  cin >> n;
  cout << "请输入初始化的元素：";
  int *items = new int[n];
  for (int i = 0; i < n; i++) { cin >> items[i]; }
  priorityQueue<int> *priority_queue = new priorityQueue<int>(items, n);
  cout << "优先级队列初始化已完成！" << endl;
  while (true) {
    char op[30];
    cin >> op;
    if (strcmp(op, "enqueue") == 0) {
      int x;
      cin >> x;
      priority_queue->enQueue(x);
    } else if (strcmp(op, "dequeue") == 0) {
      cout << "Dequeue element " << priority_queue->deQueue() << endl;
    } else if (strcmp(op, "getHead") == 0) {
      cout << "Head element is " << priority_queue->getHead() << endl;
    } else if (strcmp(op, "exit") == 0) {
      break;
    } else {
      cout << "Invalid Operation!" << endl;
    }
  }
  return 0;
}