// 代码清单7-4至7-5 堆排序
// 样例输入：
// 请输入待排序数组的元素个数： 4
// 请依次输入待排序数组元素(按照key，other的形式)：
// 1 1
// 4 4
// 7 2
// 3 6
// 样例输出：
// 堆排序后的数组元素为：
// 1 1
// 3 6
// 4 4
// 7 2
#include <iostream>

#include "../chapter5/set.h"

using namespace std;

template <class KEY, class OTHER>
void heapSort(SET<KEY, OTHER> a[], int size) {
  int i;
  SET<KEY, OTHER> tmp;

  // 创建初始的堆
  for (i = size / 2 - 1; i >= 0; i--) percolateDown(a, i, size);

  // 执行n-1次出队操作
  for (i = size - 1; i > 0; --i) {
    tmp = a[0];
    a[0] = a[i];
    a[i] = tmp;  // delete  a[0]
    percolateDown(a, 0, i);
  }
}

template <class KEY, class OTHER>
void percolateDown(SET<KEY, OTHER> a[], int hole, int size) {
  int child;
  SET<KEY, OTHER> tmp = a[hole];

  for (; hole * 2 + 1 < size; hole = child) {
    child = hole * 2 + 1;
    if (child != size - 1 && a[child + 1].key > a[child].key) child++;
    if (a[child].key > tmp.key)
      a[hole] = a[child];
    else
      break;
  }
  a[hole] = tmp;
}

SET<int, int> a[100000];
int main() {
  cout << "请输入待排序数组的元素个数：";
  int n;
  cin >> n;

  cout << "\n请依次输入待排序数组元素(按照key，other的形式)：\n";
  for (int i = 0; i < n; i++) { cin >> a[i].key >> a[i].other; }
  heapSort(a, n);
  cout << "\n堆排序后的数组元素为：\n";
  for (int i = 0; i < n; i++) {
    cout << a[i].key << ' ' << a[i].other << endl;
  }
}
