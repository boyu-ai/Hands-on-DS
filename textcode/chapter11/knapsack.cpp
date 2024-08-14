// 代码清单11-5 01背包问题
// 样例输入：
// 4 5
// 1 4
// 2 5
// 3 5
// 1 1
// 样例输出：
// 10
#include <iostream>
using namespace std;
int dp[10000][10000] = {0};
int weights[10000] = {0};
int values[10000] = {0};

int knapsack(int W, int n) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= W; j++) {
      if (weights[i - 1] <= j) {
        dp[i][j] =
            max(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + values[i - 1]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  return dp[n][W];
}

int main() {
  int n, W;
  cin >> n >> W;
  for (int i = 0; i < n; i++)
    cin >> weights[i] >> values[i];
  int max_value = knapsack(W, n);
  cout << max_value << endl;
  return 0;
}