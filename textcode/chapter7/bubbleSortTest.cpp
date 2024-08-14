// 代码清单7-6 冒泡排序
// 样例输入：
// 请输入待排序数组的元素个数： 4
// 请依次输入待排序数组元素(按照key，other的形式)：
// 1 1
// 4 4
// 7 2
// 3 6
// 样例输出：
// 冒泡排序后的数组元素为：
// 1 1
// 3 6
// 4 4
// 7 2
#include <iostream>

#include "../chapter5/set.h"

using namespace std;
template <class KEY, class OTHER>
void bubbleSort(SET<KEY, OTHER> a[], int size) {
  int i, j;
  SET<KEY, OTHER> tmp;
  bool flag = true;  // 记录一趟起泡中有没有进行过数据元素的交换

  for (i = 1; i < size && flag; ++i) {  // (size-1)趟起泡
    flag = false;
    for (j = 0; j < size - i; ++j)  // 第i趟起泡
      if (a[j + 1].key < a[j].key) {
        tmp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = tmp;
        flag = true;
      }
  }
}

SET<int, int> a[100000];
int main() {
  cout << "请输入待排序数组的元素个数：";
  int n;
  cin >> n;

  cout << "\n请依次输入待排序数组元素(按照key，other的形式)：\n";
  for (int i = 0; i < n; i++) { cin >> a[i].key >> a[i].other; }
  bubbleSort(a, n);
  cout << "\n冒泡排序后的数组元素为：\n";
  for (int i = 0; i < n; i++) {
    cout << a[i].key << ' ' << a[i].other << endl;
  }
}
