// 代码清单1-4 最大连续子序列和的O(nlogn)递归算法及其测试程序 
// 输入序列长度n，以及序列中的数字a[i]，输出最大连续子序列的和以及子序列的终点和起点
// 样例输入：
// 5
// 2 3 -1 2 -3
// 样例输出：
// 最大连续子序列和为：6
// 子序列的起点：0，子序列的终点：3
#include <iostream>
using namespace std;

// 递归解决方案
int maxSum(int a[], int left, int right, int &start, int &end) {
  int maxLeft, maxRight, center;
  // maxLeft和maxRight分别为前半部分、后半部分的最大连续子序列和
  int leftSum = 0, rightSum = 0;  // 情况3中，左、右半段的连续子序列和
  int maxLeftTmp = 0,
      maxRightTmp = 0;  // 情况3中，情况3中，左、右半段的最大连续子序列和
  int startL, startR, endL,
      endR;  // 前半部分、后半部分的最大连续子序列的起点和终点

  if (left == right) {  // 仅有一个元素，递归终止
    start = end = left;
    return a[left] > 0 ? a[left] : 0;
  }

  center = (left + right) / 2;
  // 找前半部分的最大连续子序列和
  maxLeft = maxSum(a, left, center, startL, endL);
  // 找后半部分的最大连续子序列和
  maxRight = maxSum(a, center + 1, right, startR, endR);

  // 找从前半部分开始但在后半部分结束的最大连续子序列
  start = center;
  for (int i = center; i >= left; --i) {
    leftSum += a[i];
    if (leftSum > maxLeftTmp) {
      maxLeftTmp = leftSum;
      start = i;
    }
  }
  end = center + 1;
  for (int i = center + 1; i <= right; ++i) {
    rightSum += a[i];
    if (rightSum > maxRightTmp) {
      maxRightTmp = rightSum;
      end = i;
    }
  }
  // 找3种情况中的最大连续子序列和
  if (maxLeft > maxRight)
    if (maxLeft > maxLeftTmp + maxRightTmp) {
      start = startL;
      end = endL;
      return maxLeft;
    } else
      return maxLeftTmp + maxRightTmp;
  else if (maxRight > maxLeftTmp + maxRightTmp) {
    start = startR;
    end = endR;
    return maxRight;
  } else
    return maxLeftTmp + maxRightTmp;
}

// 包裹函数
int maxSubsequenceSum(int a[], int size, int &start, int &end) {
  return maxSum(a, 0, size - 1, start, end);
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
