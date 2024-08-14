// 代码清单1-2 最大连续子序列和的枚举算法及其测试程序
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
  int maxSum = 0;  // 当前的最大连续子序列之和

  for (int i = 0; i < size; i++)      // 子序列的起始位置
    for (int j = i; j < size; j++) {  // 子序列的终止位置
      int thisSum = 0;
      for (int k = i; k <= j; k++)  // 求从i开始到j结束的序列之和
        thisSum += a[k];
      if (thisSum > maxSum) {  // 找到一个更好的序列
        maxSum = thisSum;
        start = i;
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