// seqList类的测试程序
// 插入：insert i x
// 删除：remove i
// 查找：search x
// 清除: clear
// 访问：visit i
// 结束： exit

// 输入样例：
// insert 0 1
// insert 1 2
// insert 2 3
// search 2
// remove 1
// search 2
// visit 1
// exit
// 输出样例：
// The index is 1
// Not found
// Visit element 3
// 1 3
#include <cstring>
#include <iostream>

#include "seqList.h"
using namespace std;
int main() {
  seqList<int> seqlist(20);
  while (true) {
    char op[10];
    cin >> op;

    if (strcmp(op, "insert") == 0) {
      int index, x;
      cin >> index >> x;
      if (index != seqlist.length())
        cout << "Insert index is invalid!" << endl;
      else
        seqlist.insert(index, x);
    } else if (strcmp(op, "remove") == 0) {
      int index;
      cin >> index;
      seqlist.remove(index);
    } else if (strcmp(op, "search") == 0) {
      int x;
      cin >> x;
      int res = seqlist.search(x);
      if (res == -1) {
        cout << "Not found" << endl;
      } else {
        cout << "The index is " << res << endl;
      }
    } else if (strcmp(op, "visit") == 0) {
      int i;
      cin >> i;
      if (i >= seqlist.length()) {
        cout << "Element does not exists" << endl;
        continue;
      }
      int res = seqlist.visit(i);
      cout << "Visit element " << res << endl;
    } else if (strcmp(op, "exit") == 0) {
      break;
    } else if (strcmp(op, "clear") == 0) {
      seqlist.clear();
    } else {
      cout << "Invalid operation!" << endl;
    }
  }
  seqlist.traverse();
  return 0;
}