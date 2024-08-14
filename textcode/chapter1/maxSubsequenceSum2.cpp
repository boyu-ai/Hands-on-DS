// 代码清单1-3 最大连续子序列和的O(n^2)两重循环算法及其测试程序
// 输入序列长度n，以及序列中的数字a[i]，输出最大连续子序列的和以及子序列的终点和起点
// 样例输入：
// 5
// 2 3 -1 2 -3
// 样例输出：
// 最大连续子序列和为：6
// 子序列的起点：0，子序列的终点：3
#include <iostream>
using namespace std;

int maxSubsequenceSum(int a[], int size, int &start, int &end) {
  int maxSum = 0;  // 已知的最大连续子序列之和

  for (int i = 0; i < size; i++) {    // 连续子序列的起始位置
    int thisSum = 0;                  // 从i开始的连续子序列之和
    for (int j = i; j < size; j++) {  // 连续子序列的终止位置
      thisSum += a[j];  // 计算从第i到第j个元素的连续子序列之和
      if (thisSum > maxSum) {
        maxSum = thisSum;
        start = i;
        end = j;
      }
    }
  }
  return maxSum;
}

int main(){
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int start, end;
    cout << "最大连续子序列和为：" << maxSubsequenceSum(a, n, start, end) << endl;
    cout << "子序列的起点：" << start << "，子序列的终点" << end << endl;
}