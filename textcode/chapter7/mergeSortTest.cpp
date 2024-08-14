// 代码清单7-8至7-9 归并排序
// 样例输入：
// 请输入待排序数组的元素个数： 4
// 请依次输入待排序数组元素(按照key，other的形式)：
// 1 1
// 4 4
// 7 2
// 3 6
// 样例输出：
// 归并排序后的数组元素为：
// 1 1
// 3 6
// 4 4
// 7 2
#include <iostream>

#include "../chapter5/set.h"
using namespace std;
template <class KEY, class OTHER>
void mergeSort(SET<KEY, OTHER> a[], int left, int right) {
  int mid = (left + right) / 2;

  if (left == right) return;
  mergeSort(a, left, mid);
  mergeSort(a, mid + 1, right);
  merge(a, left, mid + 1, right);
}

template <class KEY, class OTHER>
void mergeSort(SET<KEY, OTHER> a[], int size) {
  mergeSort(a, 0, size - 1);
}

template <class KEY, class OTHER>
void merge(SET<KEY, OTHER> a[], int left, int mid, int right) {
  SET<KEY, OTHER> *tmp = new SET<KEY, OTHER>[right - left + 1];

  int i = left, j = mid, k = 0;

  while (i < mid && j <= right)  // 两表都未结束
    if (a[i].key < a[j].key)
      tmp[k++] = a[i++];
    else
      tmp[k++] = a[j++];

  while (i < mid) tmp[k++] = a[i++];     // 前半部分没有结束
  while (j <= right) tmp[k++] = a[j++];  // 后半部分没有结束

  for (i = 0, k = left; k <= right;) a[k++] = tmp[i++];
  delete[] tmp;
}

SET<int, int> a[100000];
int main() {
  cout << "请输入待排序数组的元素个数：";
  int n;
  cin >> n;

  cout << "\n请依次输入待排序数组元素(按照key，other的形式)：\n";
  for (int i = 0; i < n; i++) { cin >> a[i].key >> a[i].other; }
  mergeSort(a, n);
  cout << "\n归并排序后的数组元素为：\n";
  for (int i = 0; i < n; i++) {
    cout << a[i].key << ' ' << a[i].other << endl;
  }
}
