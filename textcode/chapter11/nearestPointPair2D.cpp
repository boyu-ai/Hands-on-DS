//代码清单11-2 二维平面的最近点对算法的实现
// 样例输入：
// 4
// 1 1
// 2 3
// 4 5
// 5 4
// 样例输出：(即点对(4,5)和(5,4)的距离)
// 1.41421
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
#define Inf 1 << 31 - 1
#define MAXN 1000000
struct node {
  double x;
  double y;
};

struct node point[MAXN];
int mpt[MAXN];

double dis(node a, node b) {  // 求欧几里得距离
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool cmp1(node a, node b) {  // 按照x坐标排序
  if (a.x == b.x) return a.y < b.y;
  return a.x < b.x;
}

bool cmp2(int a, int b) {  // 第二个排序是选择中间的点
  return point[a].y < point[b].y;
}

double minDist(int left, int right) {
  // 递归求从point[left]到point[right]的点的最短距离
  double d = Inf;
  if (left == right)
    return d;  // 自己和自己不可以被选择，因此距离设成正无穷
  // 这两个点中间没有任何点，所以直接求距离
  if (left + 1 == right) return dis(point[left], point[right]);
  // 如果中间还有其他点，那就在中间分开
  int mid = (left + right) >> 1;
  double d1 = minDist(mid, right);  // 情况1: 找左边的最小距离
  double d2 = minDist(left, mid - 1);  // 情况2: 找右边的最小距离
  d = min(d1, d2);  // 求出两个最小距离中的最小值
  int k = 0;
  for (int i = left; i <= right; i++) {
    if (fabs(point[mid].x - point[i].x) <= d) { mpt[++k] = i; }
  }
  sort(mpt + 1, mpt + k + 1, cmp2);  // 按这些点的y轴坐标排序
  for (int i = 1; i <= k; i++) {
    for (int j = i + 1;
         j <= k && point[mpt[j]].y - point[mpt[i]].y <= d; j++) {
      if (d >= dis(point[mpt[i]], point[mpt[j]]))
        d = dis(point[mpt[i]], point[mpt[j]]);
    }
  }  // 线性扫描，找这些点的最小距离
  return d;
}

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> point[i].x >> point[i].y;  // 读入所有的点
  }
  sort(point + 1, point + n + 1, cmp1);  // 根据点坐标的x轴排序
  cout << minDist(1, n) << endl;
  return 0;
}