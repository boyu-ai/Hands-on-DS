//代码清单1-5 最大连续子序列和的线性算法及其测试程序
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
  int maxSum, starttmp, thisSum;
  start = end = maxSum = starttmp = thisSum = 0;
  for (int j = 0; j < size; ++j) {
    thisSum += a[j];
    if (thisSum <= 0) {  // 排除前面的连续子序列
      thisSum = 0;
      starttmp = j + 1;
    } else if (thisSum > maxSum) {  // 找到一个连续子序列和更大的连续子序列
      maxSum = thisSum;
      start = starttmp;
      end = j;
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