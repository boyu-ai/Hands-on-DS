// 代码清单3-10 排队洗衣样例代码
#include <iostream>

#include "seqQueue.h"
using namespace std;

int min(int a, int b) {
  if (a < b) return a;
  return b;
}
int max(int a, int b) {
  if (a > b) return a;
  return b;
}

int main() {
  int k;
  cout << "请输入学生个数：" << endl;
  cin >> k;
  seqQueue<int> studentQueue(k);
  cout << "请依次输入学生洗衣时长：" << endl;
  for (int i = 0; i < k; i++) {
    int t;
    cin >> t;
    studentQueue.enQueue(t);  // 创建学生洗衣服的队列
  }

  int time = 0;
  int washer1 = 0, washer2 = 0;
  if (studentQueue.isEmpty()) {  // 当天没有学生预约洗衣服
    cout << 0;
    return 0;
  } else {
    washer1 = studentQueue.deQueue();
    if (studentQueue.isEmpty()) {  // 当天只有一位学生预约洗衣服
      cout << washer1 << endl;
      return 0;
    } else {
      washer2 = studentQueue.deQueue();
      // 2台洗衣机开始完成前两位同学的洗衣请求
    }
  }
  while (!studentQueue.isEmpty()) {
    time += min(washer1, washer2);
    // 其中一台洗衣机完成了工作，总时长为time
    washer1 -= min(washer1, washer2);
    washer2 -= min(washer1, washer2);
    if (washer1 == 0) {
      washer1 = studentQueue.deQueue();
      // 洗衣机1完成了工作，新的同学开始使用洗衣机1
    } else {  // washer2 == 0
      washer2 = studentQueue.deQueue();
      // 洗衣机2完成了工作，新的同学开始使用洗衣机2
    }
  }
  cout << time + max(washer1, washer2) << endl;
  // 总时间等于已经经过的时间加上washer1和washer2中剩余需要洗衣服时间更长者的时间
  return 0;
}