// 代码清单11-4  爬楼梯问题
// 输入楼梯数n，输出爬楼梯的方案数
// 样例输入：
// 5
// 样例输出：
// 5 stairs: 8
#include <iostream>
using namespace std;
int climbStairs(int n) {
  int *dp = new int[n + 1];
  dp[0] = 1;
  dp[1] = 1;
  for (int i = 2; i <= n; ++i) 
    dp[i] = dp[i - 1] + dp[i - 2];
  return dp[n];
}

int main() {
  int n;
  cin >> n;
  int ways = climbStairs(n);
  cout << n << " stairs: " << ways << endl;
  return 0;
}