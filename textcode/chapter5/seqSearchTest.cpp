// 代码清单5-2 无序表的顺序查找实现及其测试程序
// 首先，输入初始化数据个数n，系统会自动生成n对<int,string>对
// 样例：
// 请输入初始化数据个数：10
// 生成的数据为：<7,Z> <73,C> <30,w> <44,0> <23,v> <40,J> <92,a> <87,J> <27,x> <40,a>
// 然后，可以输入search来搜索对应的key，other对
// 输入：search 30 输出：Data key:30, value:w
// 输入：search 27 输出：Data key:27, value:x
// 输入：search 22 输出：Data does not exist!
// exit
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>

#include "set.h"

using namespace std;
const int W = 100;
const string charset =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

template <class KEY, class OTHER>
int seqSearch(SET<KEY, OTHER> data[], int size, const KEY &x) {
  for (int i = 0; i < size; i++) {
    if (data[i].key == x) return i;
  }
  return -1;  // 找不到，返回-1
}

void random_initialize(SET<int, char> data[], int size) {
  cout << "生成的数据为：";
  for (int i = 0; i < size; i++) {
    int randomNumber = rand() % W;
    data[i].key = randomNumber;
    int index = rand() % charset.length();
    char randomString = charset[index];
    data[i].other = randomString;
    cout << '<' << randomNumber << ',' << randomString << "> ";
  }
  cout << endl;
}
int main() {
  int n;
  cout << "请输入初始化数据个数：";
  cin >> n;
  SET<int, char> *data = new SET<int, char>[n];
  random_initialize(data, n);
  while (true) {
    char op[30];
    cin >> op;
    if (strcmp(op, "search") == 0) {
      int x;
      cin >> x;
      int index = seqSearch(data, n, x);
      if (index == -1)
        cout << "Data does not exist!" << endl;
      else {
        cout << "Data key:" << data[index].key
             << ", value:" << data[index].other << endl;
      }
    } else if (strcmp(op, "exit") == 0) {
      break;
    } else {
      cout << "Invalid Operation!" << endl;
    }
  }
  return 0;
}
