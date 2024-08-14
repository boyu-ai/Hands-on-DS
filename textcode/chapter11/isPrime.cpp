// 代码清单11-1 判断数字是否为质数的测试程序
// 输入数字，返回是否为素数的结果
// 样例输入：
// 11
// 样例输出：
// 该数字是素数
#include <iostream>
#include <cmath>
using namespace std;
bool isPrime(int n) {
  if (n == 1 || n == 2) return true;
  int sq = int(sqrt(n));
  for (int factor = 2; factor < sq; factor++) {
    if (n % factor == 0) return false;
  }
  return true;
}

int main() {
  cout << "请输入待判断的数字：";
  int n;
  cin >> n;
  cout << "该数字" << (isPrime(n) ? "是" : "不是") << "素数" << endl;
}
