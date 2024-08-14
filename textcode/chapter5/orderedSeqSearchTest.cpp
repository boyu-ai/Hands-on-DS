// 代码清单5-4 有序表的顺序查找实现及其测试程序
// 首先，输入初始化数据个数n，系统会自动生成n对<int,string>对并排序
// 样例：
// 请输入初始化数据个数：10
// 生成的数据为：<7,Z> <23,v> <27,x> <30,w> <40,J> <40,a> <44,0> <73,C> <87,J> <92,a> 
// 然后，可以输入search来搜索对应的key，other对
// 输入：search 23 输出：Data key:23, value:v 
// 输入：search 40 输出：Data key:40, value:J
// 输入：search 22 输出：Data does not exist!
// exit
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "set.h"

using namespace std;

const int W = 100;
const string charset =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

template <class KEY, class OTHER>
int seqSearch(SET<KEY, OTHER> data[], int size, const KEY &x) {
  data[0].key = x;
  int i;
  for (i = size; x < data[i].key; --i);
  if (x == data[i].key)
    return i;
  else
    return 0;
}

void random_initialize(SET<int, char> *data, int size) {
  cout << "生成的数据为：";
  for (int i = 0; i < size; i++) {
    int randomNumber = rand() % W;
    data[i + 1].key = randomNumber;
    int index = rand() % charset.length();
    char randomString = charset[index];
    data[i + 1].other = randomString;
  }
  sort(data + 1, size);
  for (int i = 0; i < size; i++) {
    cout << '<' << data[i + 1].key << ',' << data[i + 1].other << "> ";
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
      if (index == 0)
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
