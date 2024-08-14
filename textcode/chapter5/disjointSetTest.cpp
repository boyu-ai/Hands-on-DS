// 不相交集的测试程序
// 首先，输入并查集集合元素个数
// 请输入并查集集合元素个数：10
// 接下来可以输入join命令或者find命令来执行并/查的操作
// 样例输入：
// join 5 6
// join 6 7
// find 7
// exit
// 样例输出：
// The root of 7 is: 5
#include <cstring>
#include <iostream>

#include "disjointSet.h"
using namespace std;
int main() {
  int n;
  cout << "请输入并查集集合元素个数：";
  cin >> n;
  disjointSet *disjointset = new disjointSet(n);

  while (true) {
    char op[30];
    cin >> op;
    if (strcmp(op, "join") == 0) {
      int a, b;
      cin >> a >> b;
      int roota = disjointset->find(a);
      int rootb = disjointset->find(b);
      disjointset->join(roota, rootb);
    } else if (strcmp(op, "find") == 0) {
      int x;
      cin >> x;
      cout << "The root of " << x << " is: " << disjointset->find(x) << endl;
    } else if (strcmp(op, "exit") == 0) {
      break;
    } else {
      cout << "Invalid Operation!" << endl;
    }
  }
  return 0;
}
