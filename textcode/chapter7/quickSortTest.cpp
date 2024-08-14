// 代码清单7-7 快速排序
// 样例输入：
// 请输入待排序数组的元素个数： 4
// 请依次输入待排序数组元素(按照key，other的形式)：
// 1 1
// 4 4
// 7 2
// 3 6
// 样例输出：
// 快速排序后的数组元素为：
// 1 1
// 3 6
// 4 4
// 7 2
#include <iostream>

#include "../chapter5/set.h"
using namespace std;
template <class KEY, class OTHER>
int divide(SET<KEY, OTHER> a[], int low, int high) {
  SET<KEY, OTHER> k = a[low];
  do {  // 循环直到low和high重叠
    while (low < high && a[high].key > k.key)
      --high;  // 从右向左找到小于k的值
    if (low < high) {
      a[low] = a[high];
      ++low;
    }  // 将找到的小于k的值放入low位置
    while (low < high && a[low].key <= k.key)
      ++low;  // 从左向右找到大于k的值
    if (low < high) {
      a[high] = a[low];
      --high;
    }  // 将找到的大于k的值放入high位置
  } while (low != high);
  a[low] = k;
  return low;
}
template <class KEY, class OTHER>
void quickSort(SET<KEY, OTHER> a[], int low, int high) {
  int mid;
  if (low >= high) return;  // 待分段的元素只有1个或0个，递归终止
  mid = divide(a, low, high);
  quickSort(a, low, mid - 1);   // 排序左边一半
  quickSort(a, mid + 1, high);  // 排序右边一半
}

template <class KEY, class OTHER>
void quickSort(SET<KEY, OTHER> a[], int size) {  // 包裹函数
  quickSort(a, 0, size - 1);
}

SET<int, int> a[100000];
int main() {
  cout << "请输入待排序数组的元素个数：";
  int n;
  cin >> n;

  cout << "\n请依次输入待排序数组元素(按照key，other的形式)：\n";
  for (int i = 0; i < n; i++) { cin >> a[i].key >> a[i].other; }
  quickSort(a, n);
  cout << "\n快速排序后的数组元素为：\n";
  for (int i = 0; i < n; i++) {
    cout << a[i].key << ' ' << a[i].other << endl;
  }
}
