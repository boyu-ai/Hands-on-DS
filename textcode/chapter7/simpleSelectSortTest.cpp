// 代码清单7-3 直接选择排序
// 样例输入：
// 请输入待排序数组的元素个数： 4
// 请依次输入待排序数组元素(按照key，other的形式)：
// 1 1
// 4 4
// 7 2
// 3 6
// 样例输出：
// 选择排序后的数组元素为：
// 1 1
// 3 6
// 4 4
// 7 2
#include <iostream>

#include "../chapter5/set.h"

using namespace std;
template <class KEY, class OTHER>
void simpleSelectSort(SET<KEY, OTHER> a[], int size) {
  int i, j, min;
  SET<KEY, OTHER> tmp;

  for (i = 0; i < size - 1; ++i) {
    min = i;
    for (j = i + 1; j < size; ++j)
      if (a[j].key < a[min].key) min = j;
    tmp = a[i];
    a[i] = a[min];
    a[min] = tmp;
  }
}

SET<int, int> a[100000];
int main() {
  cout << "请输入待排序数组的元素个数：";
  int n;
  cin >> n;

  cout << "\n请依次输入待排序数组元素(按照key，other的形式)：\n";
  for (int i = 0; i < n; i++) { cin >> a[i].key >> a[i].other; }
  simpleSelectSort(a, n);
  cout << "\n选择排序后的数组元素为：\n";
  for (int i = 0; i < n; i++) {
    cout << a[i].key << ' ' << a[i].other << endl;
  }
}
